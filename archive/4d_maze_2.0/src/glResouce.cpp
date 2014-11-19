#include "global.h"
#include "wingdi.h"
#include "glResouce.h"
#include "Tips.h"
#include "Maze4D.h"

// 纹理： 0墙X 1墙Y 2天花板 3地板
CglResouce::CglResouce()
    :LwallX(0),LwallY(0),Lground(0),Lceiling(0),hFont(NULL)
{
}

CglResouce::~CglResouce()
{
    glDeleteTextures(IMG_SUM,texture);
    glDeleteLists(1,Lceiling);
    glDeleteLists(1,Lground);
    glDeleteLists(1,LwallX);
    glDeleteLists(1,LwallY);
    if(hFont) DeleteObject(hFont);
}

int CglResouce::LoadGLTextures(int level){
    int SucessAmount = 0; // 纹理载入成功的数目
    char s[30];

    AUX_RGBImageRec *TextureImage[IMG_SUM]; // Create Storage Space For The Texture

    sprintf_s(s,"texture/1 wall x.bmp");
    TextureImage[ 0 ]=auxDIBImageLoad( s ); // 墙X
    sprintf_s(s,"texture/1 wall y.bmp");
    TextureImage[ 1 ]=auxDIBImageLoad( s ); // 墙Y
    sprintf_s(s,"texture/1 ceiling.bmp");
    TextureImage[ 2 ]=auxDIBImageLoad( s ); // 天花板
    sprintf_s(s,"texture/1 ground.bmp");
    TextureImage[ 3 ]=auxDIBImageLoad( s ); // 地板

    glGenTextures(IMG_SUM, texture); // Create The Texture
    for( int i=0; i<IMG_SUM; i++ ){ // 检查所有纹理是否载入成功，并生成纹理
        if( TextureImage[i] && TextureImage[i]->data){
            SucessAmount++; // 成功载入一个纹理
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY,
                0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY,
                GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
            free(TextureImage[i]->data); // Free The Texture Image Memory
            free(TextureImage[i]); // Free The Image Structure
        }// if
    }// for

    return (SucessAmount == IMG_SUM); // Return The Status
}

void CglResouce::BuildWall(){
    // 建立所有墙面的显示列表
    double pos=0.5f,neg=-0.5f;
    double nearly=0.99999f;

    // 墙X，在x轴负方向
    LwallX = glGenLists(1);
    glNewList( LwallX, GL_COMPILE );
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f); glVertex3f( neg,pos,pos );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( neg,neg,pos );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( neg,neg,neg );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( neg,pos,neg );
    glEnd();
    glEndList();

    // 墙Y，在Y轴负方向
    LwallY = glGenLists(1);
    glNewList( LwallY, GL_COMPILE );
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f); glVertex3f( pos,neg,pos );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( neg,neg,pos );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( neg,neg,neg );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( pos,neg,neg );
    glEnd();
    glEndList();

    // 天花板，在Z轴正方向
    Lceiling = glGenLists(1);
    glNewList( Lceiling, GL_COMPILE );
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f); glVertex3f( neg,pos,pos*nearly );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( pos,pos,pos*nearly );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( pos,neg,pos*nearly );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( neg,neg,pos*nearly );
    glEnd();
    glEndList();

    // 地板，在Z轴负向
    Lground = glGenLists(1);
    glNewList( Lground, GL_COMPILE );
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f); glVertex3f( neg,neg,neg*nearly );
    glTexCoord2f(1.0f, 0.0f); glVertex3f( pos,neg,neg*nearly );
    glTexCoord2f(1.0f, 1.0f); glVertex3f( pos,pos,neg*nearly );
    glTexCoord2f(0.0f, 1.0f); glVertex3f( neg,pos,neg*nearly );
    glEnd();
    glEndList();
}

vector<int> CglResouce::Build3DText(unsigned char *str)
{
    vector<int> result;
    result.clear();

    HDC hDC=wglGetCurrentDC();
    //设置当前字体
    SelectObject(wglGetCurrentDC(),hFont);

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

        wglUseFontOutlines(hDC,dwChar,1,result.back(),0.0,0.1f,WGL_FONT_POLYGONS,pgmf);

    }
    return result;
}

void CglResouce::BuildFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout)
{
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

void CglResouce::drawCNString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // 计算字符的个数
    // 如果是双字节字符的（比如中文字符），两个字节才算一个字符
    // 否则一个字节算一个字符
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // 将混合字符转化为宽字符
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // 逐个输出字符
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // 回收所有临时资源
    free(wstring);
    glDeleteLists(list, 1);
}

// void CglResouce::selectFont(int size, int charset, const char* face) {  
//     HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,  
//         charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  
//         DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);  
//     HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);  
//     DeleteObject(hOldFont);  
// }
// void CglResouce::Init( int level )
// {
//     if( !LoadGLTextures(level) ) exit(0);
//     BuildWall();
// }
