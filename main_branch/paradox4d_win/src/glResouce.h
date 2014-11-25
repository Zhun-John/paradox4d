#pragma once
#include "global.h"

enum GRES_WALL{
	GW_WALL_X,
	GW_WALL_Y,
	GW_CEILING,
	GW_GROUND,
	GW_SUM
} ;

class CglResouce
{
private:
    GLuint texture[GW_SUM];		// 纹理
    GLuint wall[GW_SUM];		// 四种平面的显示列表

public:
    CglResouce(){
		memset(texture,0,sizeof(texture));
		memset(wall,0,sizeof(wall));
	};
    ~CglResouce(){
		if(texture[0]!=0){
			glDeleteTextures(GW_SUM,texture);
			memset(texture,0,sizeof(texture));
		}
		if(wall[0]!=0){
			glDeleteLists(GW_SUM,wall[0]);
			memset(wall,0,sizeof(wall));
		}
	}

public:
	void LoadData(int level){
		if(texture[0]!=0){
			glDeleteTextures(GW_SUM,texture);
			memset(texture,0,sizeof(texture));
		}
		if(wall[0]!=0){
			glDeleteLists(GW_SUM,wall[0]);
			memset(wall,0,sizeof(wall));
		}

		LoadGLTextures(level);
		BuildWall();
	}

	void DrawWall(GRES_WALL id){
		glCallList(wall[id]);
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

		AUX_RGBImageRec *TextureImage[GW_SUM]; // Create Storage Space For The Texture

		sprintf_s(s,"texture/%d wall x.bmp",level);
		TextureImage[ GW_WALL_X ]=auxDIBImageLoad( s ); // 墙X
		sprintf_s(s,"texture/%d wall y.bmp",level);
		TextureImage[ GW_WALL_Y ]=auxDIBImageLoad( s ); // 墙Y
		sprintf_s(s,"texture/%d ceiling.bmp",level);
		TextureImage[ GW_CEILING ]=auxDIBImageLoad( s ); // 天花板
		sprintf_s(s,"texture/%d ground.bmp",level);
		TextureImage[ GW_GROUND ]=auxDIBImageLoad( s ); // 地板

		glGenTextures(GW_SUM, texture); // Create The Texture
		for( int i=0; i<GW_SUM; i++ ){ // 检查所有纹理是否载入成功，并生成纹理
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

		return (SucessAmount == GW_SUM); // Return The Status
	}

	// 建立所有墙面的显示列表
    void BuildWall(){
		double pos=0.5,neg=-0.5;
		double nearly=0.99999;
		glGenTextures(GW_SUM, wall); // Create The Texture

		// 墙X，在x轴负方向
		glNewList( wall[GW_WALL_X], GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[GW_WALL_X]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( neg,pos,pos );
		glTexCoord2d(1.0, 0.0); glVertex3d( neg,neg,pos );
		glTexCoord2d(1.0, 1.0); glVertex3d( neg,neg,neg );
		glTexCoord2d(0.0, 1.0); glVertex3d( neg,pos,neg );
		glEnd();
		glEndList();

		// 墙Y，在Y轴负方向
		glNewList( wall[GW_WALL_Y], GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[GW_WALL_Y]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( pos,neg,pos );
		glTexCoord2d(1.0, 0.0); glVertex3d( neg,neg,pos );
		glTexCoord2d(1.0, 1.0); glVertex3d( neg,neg,neg );
		glTexCoord2d(0.0, 1.0); glVertex3d( pos,neg,neg );
		glEnd();
		glEndList();

		// 天花板，在Z轴正方向
		glNewList( wall[GW_CEILING], GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[GW_CEILING]);
		glBegin( GL_QUADS );
		glTexCoord2d(0.0, 0.0); glVertex3d( neg,pos,pos*nearly );
		glTexCoord2d(1.0, 0.0); glVertex3d( pos,pos,pos*nearly );
		glTexCoord2d(1.0, 1.0); glVertex3d( pos,neg,pos*nearly );
		glTexCoord2d(0.0, 1.0); glVertex3d( neg,neg,pos*nearly );
		glEnd();
		glEndList();

		// 地板，在Z轴负向
		glNewList( wall[GW_GROUND], GL_COMPILE );
		glBindTexture(GL_TEXTURE_2D, texture[GW_GROUND]);
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
