#pragma once
#include "global.h"

// 所有提示文字信息，某些作为3D字体摆在空间中，某些以Hud字体打印在屏幕上
class ETips
{// Tips类职责是保存文字信息，并渲染Hud/3D文字。它不关注这些外部的坐标变换
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
    //载入所有文字数据
	void LoadData();

	void DrawRoadSign(int n){
		glCallList(font3D[0][n]);
	}

	//渲染一行3D文字，参数为其在font3D中的下标
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

	//渲染一行Hud文字，参数为其在fontHud中的下标
	void DrawHudString(int line){
		glPushMatrix();
		for (unsigned i=0; i<fontHud[line].size(); i++)
		{
			glCallList(fontHud[line][i]);
		}
		glPopMatrix();
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

};
