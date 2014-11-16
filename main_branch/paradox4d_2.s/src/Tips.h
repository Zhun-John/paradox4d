#pragma once
#include "global.h"

// ������ʾ������Ϣ��ĳЩ��Ϊ3D������ڿռ��У�ĳЩ��Hud�����ӡ����Ļ��
class ETips
{// Tips��ְ���Ǳ���������Ϣ����������������item��ȾHud/3D���֡�������ע��Щ���屻���ںδ�
private:
	HFONT hFont;
    //����3D�������ʾ�б�ÿ��vector<int>Ϊһ����
    vector< vector<int> > font3D;
    //����Hud���ֵ���ʾ�б�ÿ��vector<int>Ϊһ����
    vector< vector<int> > fontHud;

public:
	ETips(void):hFont(NULL){};
	~ETips(void){
		if(hFont) DeleteObject(hFont);
	};

public:
    //��ʼ��ĳһ�ص�������������
	void Init();

    //�������壬�ڿռ�����Ⱦ���Ӧ��3D����
    void Render3DTips(char item){
		glEnable(GL_BLEND);	//͸��/ɫ
		glBlendFunc(GL_DST_ALPHA,GL_ONE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
		glEnable(GL_TEXTURE_GEN_T);    
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glScaled(0.7, 0.5, 0.7);
		if( item>='1' && item<='9')//·�� һ�����������߰˾�
		{
			glPushMatrix();
			glScaled(0.7, 0.7, 0.7);
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(-0.5,-0.7,0);
			int i=item-'1';// i is in [0,8]
			glColor3d( 1-i*0.125, 1-i*0.125, i*0.125);
			glCallList(font3D[0][item-'0']);
			glPopMatrix();
		}
		else if( item=='{' || item=='}' )//����㡱 ���յ㡱
		{
			glPushMatrix();
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d((item=='}'), (item=='{'), 0);
			Draw3DString(item=='{'? 1:2);
			glPopMatrix();
		}
		else if (item>='a' && item<='z')//"��ʾ"
		{
			glPushMatrix();
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d(1,0,1);
			Draw3DString(3);
			glPopMatrix();
		}
	// 3D����̨��
		else if ( item=='Z' )
		{
			glPushMatrix();
			glRotated((GetTickCount()/30)%360,0,1,0);
			glTranslated(0,0.1,0);
			glColor3d(0,0.5,1);
			for (int i=8; i<=11; i++)
			{
				Draw3DString(i);
				glTranslated(0,-0.2,0);
				glRotated(-30,0,1,0);
			}
			glPopMatrix();
		}

		glDisable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
		glDisable(GL_TEXTURE_GEN_T);   
		glDisable(GL_BLEND);
		glColor3d(1,1,1);
	}

    //����Ļ����Ⱦ��˵�ʡ�
    void RenderHudTips(char item,int cameraType,int level,bool showHudOnWaypoint){
		glLoadIdentity();
		glColor3d(0.6,1,0.6);
		glDisable(GL_TEXTURE_2D);//���������ǻ�ɫ���ﲻ������
		glDisable(GL_DEPTH_TEST);//����ᱻ��ס

		//map< char, vector<string> >::iterator it = fontHud.find('=');
		//������ʾ�ؿ���Ϣ
		glRasterPos2f(-0.2,-0.9);
		DrawHudString(16+level-1);
		glRasterPos2f(0.6,-0.9);
		DrawHudString(0+cameraType);

		//��ʾ�����յ������
		if( item=='{' || item=='}' ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( (item=='{'?24:32) +level-1);
		}
		//��ʾһ������
		else if( item>='a' && item<='m' ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( 40 +item-'a');
		}
		//��ʾ���������Ӧ��̨��
		else if( item>='1' && item<='9' && showHudOnWaypoint ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( 6 +item-'0');
		}

		//���Ҵ������Ƿ񴥷���˵��
		/*if (fontHud.find(item)!=fontHud.end())
		{
			it = fontHud.find(item);
			for (unsigned i=0, n=it->second.size(); i<n; i++)
			{
				glRasterPos2f(-0.9,-0.8+0.15*(n-i));
				glRes.BuildHudText(it->second.at(i).c_str());
			}
		}*/
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}

private:
	//��������
	void BuildFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout){
		LOGFONT lf;
		lf.lfHeight = height;
		lf.lfWidth = 0;
		lf.lfEscapement = 0;
		lf.lfOrientation = 0;
		lf.lfWeight = weight;
		lf.lfItalic = italic;
		lf.lfUnderline = underline;
		lf.lfStrikeOut = strikeout;
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfOutPrecision = OUT_TT_PRECIS;
		lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lf.lfQuality = DRAFT_QUALITY;
		lf.lfPitchAndFamily = VARIABLE_PITCH | TMPF_TRUETYPE | FF_MODERN;
		strcpy_s(lf.lfFaceName,facename);
		// ��������
		hFont = CreateFontIndirect(&lf);
	}

	//����һ���ı���3D����
	vector<int> Build3DText(const char *text){
		unsigned char *str=(unsigned char *)text;
		vector<int> result;
		result.clear();

		HDC hDC=wglGetCurrentDC();
		SelectObject(hDC,hFont);

		DWORD dwChar;
		GLYPHMETRICSFLOAT pgmf[1];
		for(size_t i=0;i<strlen((char *)str);i++)
		{
			if(IsDBCSLeadByte(str[i]))
			{
				dwChar=(DWORD)((str[i]<<8)|str[i+1]);
				i++;
			}
			else
				dwChar=str[i];

			result.push_back( glGenLists(1) );

			wglUseFontOutlines(hDC,dwChar,1,result.back(),1.0f,0.1f,WGL_FONT_POLYGONS,pgmf);
		}
		return result;
	}

	//����һ���ı���Hud����
	vector<int> BuildHudText(const char* text){
		vector<int> result;
		result.clear();

		HDC hDC = wglGetCurrentDC();
		SelectObject(hDC,hFont);

		// �����ַ��ĸ���
		// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
		// ����һ���ֽ���һ���ַ�
		int len=0, i;
		for(i=0; text[i]!='\0'; ++i)
		{
			if( IsDBCSLeadByte(text[i]) )
				++i;
			++len;
		}

		// ������ַ�ת��Ϊ���ַ���ʹ�ÿ��ַ��������������롿
		wchar_t* wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text, -1, wstring, len);
		wstring[len] = L'\0';

		// �������ַ�
		for(i=0; i<len; ++i)
		{
			result.push_back( glGenLists(1) );
			wglUseFontBitmapsW(hDC, wstring[i], 1, result.back());
		}

		// ����������ʱ��Դ
		free(wstring);
		return result;
	}

    //��Ⱦһ��3D���֣�����Ϊ����font3D�е��±�
    void Draw3DString(int line){
		glPushMatrix();
		double scale = 1.0f/font3D[line].size();
		glScaled( scale, pow(scale,0.75), pow(scale,0.75) );
		glTranslated(-0.5*font3D[line].size(),0,0);

		for (unsigned i=0; i<font3D[line].size(); i++)
		{
			glCallList(font3D[line][i]);
		}
		glPopMatrix();
	}
	//��Ⱦһ��Hud���֣�����Ϊ����fontHud�е��±�
	void DrawHudString(int line){
		glPushMatrix();
		for (unsigned i=0; i<fontHud[line].size(); i++)
		{
			glCallList(fontHud[line][i]);
		}
		glPopMatrix();
	}
};
