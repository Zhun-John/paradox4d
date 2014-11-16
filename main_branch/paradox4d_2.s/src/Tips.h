#pragma once
#include "global.h"

// 所有提示文字信息，某些作为3D字体摆在空间中，某些以Hud字体打印在屏幕上
class ETips
{// Tips类职责是保存文字信息，并根据物体索引item渲染Hud/3D文字。它不关注这些物体被摆在何处
private:
	HFONT hFont;
    //所有3D字体的显示列表，每个vector<int>为一行字
    vector< vector<int> > font3D;
    //所有Hud文字的显示列表，每个vector<int>为一行字
    vector< vector<int> > fontHud;

public:
	ETips(void):hFont(NULL){};
	~ETips(void){
		if(hFont) DeleteObject(hFont);
	};

public:
    //初始化某一关的所有文字数据
	void Init();

    //根据物体，在空间中渲染其对应的3D文字
    void Render3DTips(char item){
		glEnable(GL_BLEND);	//透视/色
		glBlendFunc(GL_DST_ALPHA,GL_ONE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
		glEnable(GL_TEXTURE_GEN_T);    
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glScaled(0.7, 0.5, 0.7);
		if( item>='1' && item<='9')//路标 一二三四五六七八九
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
		else if( item=='{' || item=='}' )//“起点” “终点”
		{
			glPushMatrix();
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d((item=='}'), (item=='{'), 0);
			Draw3DString(item=='{'? 1:2);
			glPopMatrix();
		}
		else if (item>='a' && item<='z')//"提示"
		{
			glPushMatrix();
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d(1,0,1);
			Draw3DString(3);
			glPopMatrix();
		}
	// 3D字体台词
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

		glDisable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
		glDisable(GL_TEXTURE_GEN_T);   
		glDisable(GL_BLEND);
		glColor3d(1,1,1);
	}

    //在屏幕上渲染解说词。
    void RenderHudTips(char item,int cameraType,int level,bool showHudOnWaypoint){
		glLoadIdentity();
		glColor3d(0.6,1,0.6);
		glDisable(GL_TEXTURE_2D);//否则字体是灰色，达不到纯白
		glDisable(GL_DEPTH_TEST);//否则会被盖住

		//map< char, vector<string> >::iterator it = fontHud.find('=');
		//永久显示关卡信息
		glRasterPos2f(-0.2,-0.9);
		DrawHudString(16+level-1);
		glRasterPos2f(0.6,-0.9);
		DrawHudString(0+cameraType);

		//显示起点或终点的文字
		if( item=='{' || item=='}' ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( (item=='{'?24:32) +level-1);
		}
		//显示一行文字
		else if( item>='a' && item<='m' ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( 40 +item-'a');
		}
		//显示数字物体对应的台词
		else if( item>='1' && item<='9' && showHudOnWaypoint ){
			glRasterPos2f(-0.9,-0.7);
			DrawHudString( 6 +item-'0');
		}

		//查找此物体是否触发解说词
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
	//建立字体
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
		// 创建字体
		hFont = CreateFontIndirect(&lf);
	}

	//建立一串文本的3D字体
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

	//建立一串文本的Hud字体
	vector<int> BuildHudText(const char* text){
		vector<int> result;
		result.clear();

		HDC hDC = wglGetCurrentDC();
		SelectObject(hDC,hFont);

		// 计算字符的个数
		// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
		// 否则一个字节算一个字符
		int len=0, i;
		for(i=0; text[i]!='\0'; ++i)
		{
			if( IsDBCSLeadByte(text[i]) )
				++i;
			++len;
		}

		// 将混合字符转化为宽字符【使用宽字符，避免中文乱码】
		wchar_t* wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text, -1, wstring, len);
		wstring[len] = L'\0';

		// 逐个输出字符
		for(i=0; i<len; ++i)
		{
			result.push_back( glGenLists(1) );
			wglUseFontBitmapsW(hDC, wstring[i], 1, result.back());
		}

		// 回收所有临时资源
		free(wstring);
		return result;
	}

    //渲染一行3D文字，参数为其在font3D中的下标
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
	//渲染一行Hud文字，参数为其在fontHud中的下标
	void DrawHudString(int line){
		glPushMatrix();
		for (unsigned i=0; i<fontHud[line].size(); i++)
		{
			glCallList(fontHud[line][i]);
		}
		glPopMatrix();
	}
};
