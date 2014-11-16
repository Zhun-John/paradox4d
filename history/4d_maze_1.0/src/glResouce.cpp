#include "glResouce.h"
#include "Info.h"
#include "Maze4D.h"

// ���� 0ǽ 1�컨�� 2�ذ� 
CglResouce::CglResouce()
    :Lwall(0),Lground(0),Lceiling(0),hFont(NULL)
{
}

CglResouce::~CglResouce()
{
    glDeleteTextures(IMG_SUM,texture);
    glDeleteLists(LIST_SUM,Lwall);
    if(hFont) DeleteObject(hFont);
}

int CglResouce::LoadGLTextures(int level){
    int SucessAmount = 0;									// ��������ɹ�����Ŀ
    char s[30];

    AUX_RGBImageRec *TextureImage[IMG_SUM];					// Create Storage Space For The Texture
    
    sprintf_s(s,"texture/%d Wall.bmp",level);
    TextureImage[ 0 ]=auxDIBImageLoad( s );					// ǽ
    sprintf_s(s,"texture/%d Ceiling.bmp",level);
    TextureImage[ 1 ]=auxDIBImageLoad( s );				// �컨��
    sprintf_s(s,"texture/%d Ground.bmp",level);
    TextureImage[ 2 ]=auxDIBImageLoad( s );				// �ذ�

    glGenTextures(IMG_SUM, texture);			// Create The Texture
    for( int i=0; i<IMG_SUM; i++ ){	// ������������Ƿ�����ɹ�������������
        if( TextureImage[i] && TextureImage[i]->data){
            SucessAmount++;								// �ɹ�����һ������
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 
                0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY,
                GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data); 
            free(TextureImage[i]->data);					// Free The Texture Image Memory
            free(TextureImage[i]);								// Free The Image Structure
        }// if
    }// for

    return (SucessAmount == IMG_SUM);					// Return The Status
}

void CglResouce::BuildWall(){
    // ��������ǽ�����ʾ�б�
    float pos=0.5f,neg=-0.5f;

    Lwall = glGenLists( LIST_SUM );
    glNewList( Lwall, GL_COMPILE );  // ��x�Ḻ����
    glBindTexture(GL_TEXTURE_2D, texture[ 0 ]);
    //glColor3f( 1.0f,0.0f,0.0f );
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f);	glVertex3f( neg,pos,pos );
    glTexCoord2f(1.0f, 0.0f);	glVertex3f( neg,neg,pos );
    glTexCoord2f(1.0f, 1.0f);	glVertex3f( neg,neg,neg );
    glTexCoord2f(0.0f, 1.0f);	glVertex3f( neg,pos,neg );
    glEnd();
    glEndList();

    Lceiling = Lwall + 1;
    glNewList( Lceiling, GL_COMPILE );  // �컨��
    glBindTexture(GL_TEXTURE_2D, texture[ 1]);
    //glColor3f( 0.0f,1.0f,0.0f );
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f);	glVertex3f( neg,pos,pos*0.999 );
    glTexCoord2f(1.0f, 0.0f);	glVertex3f( pos,pos,pos*0.999 );
    glTexCoord2f(1.0f, 1.0f);	glVertex3f( pos,neg,pos*0.999 );
    glTexCoord2f(0.0f, 1.0f);	glVertex3f( neg,neg,pos*0.999 );
    glEnd();
    glEndList();

    Lground = Lceiling + 1;
    glNewList( Lground, GL_COMPILE );  // �ذ�
    glBindTexture(GL_TEXTURE_2D, texture[ 2 ]);
    //glColor3f( 0.0f,0.0f,1.0f );
    glBegin( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f);	glVertex3f( neg,neg,neg*0.999 );
    glTexCoord2f(1.0f, 0.0f);	glVertex3f( pos,neg,neg*0.999 );
    glTexCoord2f(1.0f, 1.0f);	glVertex3f( pos,pos,neg*0.999 );
    glTexCoord2f(0.0f, 1.0f);	glVertex3f( neg,pos,neg*0.999 );
    glEnd();
    glEndList();
}

void CglResouce::InitGL( void )
{
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( WINDOW_WID, WINDOW_HEI );
    glutInitWindowPosition( 0,0 );
    glutCreateWindow( "3D�Թ�" );
    glutFullScreen();
    glutSetCursor( GLUT_CURSOR_NONE );

    glEnable(GL_TEXTURE_2D);							// ��������ӳ��
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glMatrixMode( GL_PROJECTION );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightposition[] = {0.0, 10.0, 30.0, 1.0 };
    float lightAmbient[] = { 0.5, 0.5, 0.5, 1 };
    float lightDiffuse[] = { 1,1,1,1 };
    float matAmbient[] = { 1,1,1,1 };
    float matDiffuse[] = { 0,0,1,1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
    glDisable(GL_LIGHTING);

    this->CreateFont("����",20,20,0,0,0);  
}

void CglResouce::Init( int level )
{
    if( !LoadGLTextures(level) )	exit(0);
    BuildWall();  
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

void CglResouce::CreateFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout)
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
