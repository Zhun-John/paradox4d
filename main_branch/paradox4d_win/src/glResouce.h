#pragma once
#include "global.h"

// 纹理： 0墙X 1墙Y 2天花板 3地板
#define IMG_SUM 4			// 纹理总数

class CglResouce
{
private:
    GLuint texture[IMG_SUM];		// 纹理
public:
    GLuint LwallX,LwallY,Lceiling,Lground;		// 四种平面的显示列表
public:
	// 纹理： 0墙X 1墙Y 2天花板 3地板
    CglResouce():LwallX(0),LwallY(0),Lground(0),Lceiling(0){};
    ~CglResouce(){
		glDeleteTextures(IMG_SUM,texture);
		glDeleteLists(1,Lceiling);
		glDeleteLists(1,Lground);
		glDeleteLists(1,LwallX);
		glDeleteLists(1,LwallY);
	}

public:
	//初始化OpenGL
	void InitOpenGL( int windowWidth, int windowHeight )
	{
		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
		glutInitWindowSize( windowWidth, windowHeight );
		//glutInitWindowSize( 400, 300 );
		glutInitWindowPosition( 0,0 );
		glutCreateWindow( "paradox_4d" );
		glutFullScreen();
		glutSetCursor( GLUT_CURSOR_NONE );

		glEnable(GL_TEXTURE_2D); // 启用纹理映射
		glShadeModel(GL_SMOOTH); // Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black Background
		glClearDepth(1.0f); // Depth Buffer Setup
		glEnable(GL_DEPTH_TEST); // Enables Depth Testing
		glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations


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

		LoadGLTextures(1);
		BuildWall();
	}

	//画一个3D箭头（未完成）
	void DrawArrow(){
		glPushMatrix();
		//glDisable(GL_TEXTURE_2D);
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glEnable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
		glEnable(GL_TEXTURE_GEN_T);    
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_PLANE);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_PLANE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//GL_MODULATE);

		glColor3d(0,1,1);
		glTranslated(0.5,0.5,0.5);
		glutSolidCone(0.01,0.2,16,1);
		glTranslated(0,0,0.1);
		glutSolidCone(0.02,0.1,16,1);
		
		glDisable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
		glDisable(GL_TEXTURE_GEN_T);   
		
		glDepthFunc(GL_LEQUAL);
		glPopMatrix();
	}

private:
	//载入第level关的纹理
    int LoadGLTextures(int level){
		int SucessAmount = 0; // 纹理载入成功的数目
		char s[30];

		AUX_RGBImageRec *TextureImage[IMG_SUM]; // Create Storage Space For The Texture

		sprintf_s(s,"texture/%d wall x.bmp",level);
		TextureImage[ 0 ]=auxDIBImageLoad( s ); // 墙X
		sprintf_s(s,"texture/%d wall y.bmp",level);
		TextureImage[ 1 ]=auxDIBImageLoad( s ); // 墙Y
		sprintf_s(s,"texture/%d ceiling.bmp",level);
		TextureImage[ 2 ]=auxDIBImageLoad( s ); // 天花板
		sprintf_s(s,"texture/%d ground.bmp",level);
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

	// 建立所有墙面的显示列表
    void BuildWall(){
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

//void selectFont(int size, int charset, const char* face){  
//     HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,  
//         charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  
//         DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);  
//     HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);  
//     DeleteObject(hOldFont);  
// }
// void Init( int level )
// {
//     if( !LoadGLTextures(level) ) exit(0);
//     BuildWall();
// }

};
