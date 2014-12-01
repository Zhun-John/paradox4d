#pragma once
#include "Maze4D.h"
#include "Items4D.h"
#include "glResouce.h"
#include "glFonts.h"

extern class CglResouce glRes;
extern class CglFonts fonts;

class Renderer
{
public:
	Renderer(void){}
	~Renderer(void){}

public:
	//��ʼ��OpenGL
	static void InitOpenGL()
	{
		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
#ifdef _USE_GAMEMODE
		char mode_string[20];
		sprintf_s(mode_string,"%dx%d:32@60", glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
		glutGameModeString(mode_string);
		glutEnterGameMode();
#else
		glutInitWindowSize( glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT) );
		glutInitWindowPosition( 0,0 );
		glutCreateWindow( "paradox_4d" );
		glutFullScreen();
#endif
		glutSetCursor( GLUT_CURSOR_NONE );

		glEnable(GL_TEXTURE_2D); // ��������ӳ��
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
	}

	static void ResetCamera(){
		glMatrixMode(GL_PROJECTION);//������Ļ������Ⱦ������
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

public:
	//��Ⱦ��dim��������Թ�
	static void RenderMaze( EMaze4D& maze, char dim){
		//�˴��������˸�ΪCIndex4.Iterate���������ж�����ϸ�ڵĸĶ�
		for( int iz=0; iz<maze.size.z; iz++ )
			for( int iy=0; iy<maze.size.y; iy++ )
				for( int ix=0; ix<maze.size.x-1; ix++ )
					//���Է�ǽ�ķ��񣬼���ҿɼ����򣬽��л���
					if (*maze.DataAt(ix,iy,iz,dim)!='.')
					{
						glPushMatrix();
						glTranslated( (ix+0.5), (iy+0.5), (iz+0.5) );
						glColor3d(1,1,1);

						// Y�����ǽ
						if( *maze.DataAt(ix,iy-1,iz,dim)=='.' ){
							glRes.DrawWall(GW_WALL_Y);
						}
						if( *maze.DataAt(ix,iy+1,iz,dim)=='.' ){
							glRotated( 180, 0.0f,0.0f,1.0f );
							glRes.DrawWall(GW_WALL_Y);
							glRotated( -180, 0.0f,0.0f,1.0f );
						}

						// Z������컨�塢�ذ�
						if( *maze.DataAt(ix,iy,iz-1,dim)=='.' ){
							glRes.DrawWall(GW_GROUND);
						}
						if( *maze.DataAt(ix,iy,iz+1,dim)=='.' ){
							glRes.DrawWall(GW_CEILING);
						}

						// X�����ǽ
						if( *maze.DataAt(ix-1,iy,iz,dim)=='.' ){
							glRes.DrawWall(GW_WALL_X);
						}
						if( *maze.DataAt(ix+1,iy,iz,dim)=='.' ){
							glRotated( 180, 0.0f,0.0f,1.0f );
							glRes.DrawWall(GW_WALL_X);
							glRotated( -180, 0.0f,0.0f,1.0f );
						}

						glPopMatrix();
					}
	}

	//��Ⱦdim�������3D����
	static void Render3DItem( EItem4D &item, char dim, CIndex4 size){
		CIndex4 i(0,0,0,dim);
		size.d = dim+1;
		do{
			glPushMatrix();
			glTranslated( (i.x+0.5), (i.y+0.5), (i.z+0.5) );
			glRotated(90,1,0,0);

			Render3DTips( *item.ItemAt(i) );

			glPopMatrix();
		}while( !i.IterateInside(size) );
	}

    //�������壬����Ļ����Ⱦ��˵��
    static void RenderHud(char item,int cameraType,int level,bool showHudOnWaypoint){
		glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_TEXTURE_2D);//���������ǻ�ɫ���ﲻ������
		glDisable(GL_DEPTH_TEST);//����ᱻ��ס
		glColor3d(0.6,1,0.6);

		//map< char, vector<string> >::iterator it = fontHud.find('=');
		//������ʾ�ؿ���Ϣ
		glRasterPos2d(-0.2,-0.9);
		fonts.DrawHudString(16+level-1);
		glRasterPos2d(0.6,-0.9);
		fonts.DrawHudString(0+cameraType);

		//��ʾ�����յ������
		if( item=='{' || item=='}' ){
			glRasterPos2d(-0.9,-0.7);
			fonts.DrawHudString( (item=='{'?24:32) +level-1);
		}
		//��ʾһ������
		else if( item>='a' && item<='m' ){
			glRasterPos2d(-0.9,-0.7);
			fonts.DrawHudString( 40 +item-'a');
		}
		//��ʾ���������Ӧ��̨��
		else if( item>='1' && item<='9' && showHudOnWaypoint ){
			glRasterPos2d(-0.9,-0.7);
			fonts.DrawHudString( 6 +item-'0');
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
		glPopAttrib();
		glPopMatrix();
	}

private:
	//�������壬�ڿռ�����Ⱦ���Ӧ��3D����
	static void Render3DTips(char item){
		glPushMatrix();
		glPushAttrib(GL_ENABLE_BIT);
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
			glScaled(0.7, 0.7, 0.7);
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(-0.5,-0.7,0);
			int i=item-'1';// i is in [0,8]
			glColor3d( 1-i*0.125, 1-i*0.125, i*0.125);
			fonts.DrawRoadSign(item-'0');
		}
		else if( item=='{' || item=='}' )//����㡱 ���յ㡱
		{
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d((item=='}'), (item=='{'), 0);
			fonts.Draw3DString(item=='{'? 1:2);
		}
		else if (item>='a' && item<='z')//"��ʾ"
		{
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.7,0);
			glColor3d(1,0,1);
			fonts.Draw3DString(3);
		}
		// 3D����̨��
		else if ( item=='Z' )
		{
			glRotated((GetTickCount()/30)%360,0,1,0);
			glTranslated(0,0.1,0);
			glColor3d(0,0.5,1);
			for (int i=8; i<=11; i++)
			{
				fonts.Draw3DString(i);
				glTranslated(0,-0.2,0);
				glRotated(-30,0,1,0);
			}
		}
		else if ( item=='Y' )
		{
			glRotated((GetTickCount()/10)%360,0,1,0);
			glTranslated(0,-0.2,0);
			glColor3d(0,1,0);
			for (int i=12; i<=13; i++)
			{
				fonts.Draw3DString(i);
				glTranslated(0,-0.3,0);
				glRotated(-150,0,1,0);
			}
		}

		glColor3d(1,1,1);
		glPopAttrib();
		glPopMatrix();
	}

};

