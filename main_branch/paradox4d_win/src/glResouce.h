#pragma once
#include "global.h"

// ���� 0ǽX 1ǽY 2�컨�� 3�ذ�
#define IMG_SUM 4			// ��������

class CglResouce
{
public:
    GLuint texture[IMG_SUM];		// ����
    GLuint LwallX,LwallY,Lceiling,Lground;		// ����ƽ�����ʾ�б�
public:
	// ���� 0ǽX 1ǽY 2�컨�� 3�ذ�
    CglResouce():LwallX(0),LwallY(0),Lground(0),Lceiling(0){};
    ~CglResouce(){
		glDeleteTextures(IMG_SUM,texture);
		glDeleteLists(1,Lceiling);
		glDeleteLists(1,Lground);
		glDeleteLists(1,LwallX);
		glDeleteLists(1,LwallY);
	}

public:
	//��һ��3D��ͷ��δ��ɣ�
	void DrawArrow(){
		glPushMatrix();
		//glDisable(GL_TEXTURE_2D);
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glEnable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
		glEnable(GL_TEXTURE_GEN_T);    
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_PLANE);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_PLANE);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//GL_MODULATE);

		glColor3d(0,1,1);
		glTranslated(0.5,0.5,0.5);
		glutSolidCone(0.01,0.2,16,1);
		glTranslated(0,0,0.1);
		glutSolidCone(0.02,0.1,16,1);
		
		glDisable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
		glDisable(GL_TEXTURE_GEN_T);   
		
		glDepthFunc(GL_LEQUAL);
		glPopMatrix();
	}

	//�����level�ص�����
    int LoadGLTextures(int level){
		int SucessAmount = 0; // ��������ɹ�����Ŀ
		char s[30];

		AUX_RGBImageRec *TextureImage[IMG_SUM]; // Create Storage Space For The Texture

		sprintf_s(s,"texture/%d wall x.bmp",level);
		TextureImage[ 0 ]=auxDIBImageLoad( s ); // ǽX
		sprintf_s(s,"texture/%d wall y.bmp",level);
		TextureImage[ 1 ]=auxDIBImageLoad( s ); // ǽY
		sprintf_s(s,"texture/%d ceiling.bmp",level);
		TextureImage[ 2 ]=auxDIBImageLoad( s ); // �컨��
		sprintf_s(s,"texture/%d ground.bmp",level);
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

	// ��������ǽ�����ʾ�б�
    void BuildWall(){
		double pos=0.5f,neg=-0.5f;
		double nearly=0.99999f;

		// ǽX����x�Ḻ����
		LwallX = glGenLists(1);
		glNewList( LwallX, GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( neg,pos,pos );
		glTexCoord2d(1.0, 0.0); glVertex3d( neg,neg,pos );
		glTexCoord2d(1.0, 1.0); glVertex3d( neg,neg,neg );
		glTexCoord2d(0.0, 1.0); glVertex3d( neg,pos,neg );
		glEnd();
		glEndList();

		// ǽY����Y�Ḻ����
		LwallY = glGenLists(1);
		glNewList( LwallY, GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( pos,neg,pos );
		glTexCoord2d(1.0, 0.0); glVertex3d( neg,neg,pos );
		glTexCoord2d(1.0, 1.0); glVertex3d( neg,neg,neg );
		glTexCoord2d(0.0, 1.0); glVertex3d( pos,neg,neg );
		glEnd();
		glEndList();

		// �컨�壬��Z��������
		Lceiling = glGenLists(1);
		glNewList( Lceiling, GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( neg,pos,pos*nearly );
		glTexCoord2d(1.0, 0.0); glVertex3d( pos,pos,pos*nearly );
		glTexCoord2d(1.0, 1.0); glVertex3d( pos,neg,pos*nearly );
		glTexCoord2d(0.0, 1.0); glVertex3d( neg,neg,pos*nearly );
		glEnd();
		glEndList();

		// �ذ壬��Z�Ḻ��
		Lground = glGenLists(1);
		glNewList( Lground, GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( neg,neg,neg*nearly );
		glTexCoord2d(1.0, 0.0); glVertex3d( pos,neg,neg*nearly );
		glTexCoord2d(1.0, 1.0); glVertex3d( pos,pos,neg*nearly );
		glTexCoord2d(0.0, 1.0); glVertex3d( neg,pos,neg*nearly );
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
