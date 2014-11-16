#include "global.h"
#include "wingdi.h"
#include "glResouce.h"
#include "Tips.h"
#include "Maze4D.h"

// ���� 0ǽX 1ǽY 2�컨�� 3�ذ�
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
    int SucessAmount = 0; // ��������ɹ�����Ŀ
    char s[30];

    AUX_RGBImageRec *TextureImage[IMG_SUM]; // Create Storage Space For The Texture

    sprintf_s(s,"texture/1 wall x.bmp");
    TextureImage[ 0 ]=auxDIBImageLoad( s ); // ǽX
    sprintf_s(s,"texture/1 wall y.bmp");
    TextureImage[ 1 ]=auxDIBImageLoad( s ); // ǽY
    sprintf_s(s,"texture/1 ceiling.bmp");
    TextureImage[ 2 ]=auxDIBImageLoad( s ); // �컨��
    sprintf_s(s,"texture/1 ground.bmp");
    TextureImage[ 3 ]=auxDIBImageLoad( s ); // �ذ�

    glGenTextures(IMG_SUM, texture); // Create The Texture
    for( int i=0; i<IMG_SUM; i++ ){ // ������������Ƿ�����ɹ�������������
        if( TextureImage[i] && TextureImage[i]->data){
            SucessAmount++; // �ɹ�����һ������
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
    // ��������ǽ�����ʾ�б�
    double pos=0.5f,neg=-0.5f;
    double nearly=0.99999f;

    // ǽX����x�Ḻ����
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

    // ǽY����Y�Ḻ����
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

    // �컨�壬��Z��������
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

    // �ذ壬��Z�Ḻ��
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
    //���õ�ǰ����
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
    // ��������
    hFont = CreateFontIndirect(&lf);
}

void CglResouce::drawCNString(const char* str) {
    int len, i;
    wchar_t* wstring;
    HDC hDC = wglGetCurrentDC();
    GLuint list = glGenLists(1);

    // �����ַ��ĸ���
    // �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
    // ����һ���ֽ���һ���ַ�
    len = 0;
    for(i=0; str[i]!='\0'; ++i)
    {
        if( IsDBCSLeadByte(str[i]) )
            ++i;
        ++len;
    }

    // ������ַ�ת��Ϊ���ַ�
    wstring = (wchar_t*)malloc((len+1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
    wstring[len] = L'\0';

    // �������ַ�
    for(i=0; i<len; ++i)
    {
        wglUseFontBitmapsW(hDC, wstring[i], 1, list);
        glCallList(list);
    }

    // ����������ʱ��Դ
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
