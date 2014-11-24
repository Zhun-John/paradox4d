#pragma once
#include "global.h"

// ������ʾ������Ϣ��ĳЩ��Ϊ3D������ڿռ��У�ĳЩ��Hud�����ӡ����Ļ��
class ETips
{// Tips��ְ���Ǳ���������Ϣ������ȾHud/3D���֡�������ע��Щ�ⲿ������任
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
    //����������������
	void LoadData();

	void DrawRoadSign(int n){
		glCallList(font3D[0][n]);
	}

	//��Ⱦһ��3D���֣�����Ϊ����font3D�е��±�
	void Draw3DString(int line){
		glPushMatrix();
		double scale = 1.0f/font3D[line].size();
		glScaled( scale, pow(scale,0.8), pow(scale,0.8) );

		// -0.5 is for pure chinese characters; -0.25 is for pure ascii
		glTranslated(-0.4*font3D[line].size(),0,0);

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

};
