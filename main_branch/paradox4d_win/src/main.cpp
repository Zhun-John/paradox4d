#include "global.h"
#include "glFonts.h"
#include "Items4D.h"
#include "Camera.h"
#include "Maze4D.h"
#include "glResouce.h"
#include "Plain2DCamera.h"
#include "Free3DCamera.h"
#include "Auto3DCamera.h"
#include "Vector3.h"
#include "Player.h"
#include "Progression.h"
#include "Renderer.h"

#pragma comment(lib,"GLAUX.LIB")

CglResouce glRes;
EMaze4D maze;
CglFonts fonts;
EItem4D items;
CPlayer player;
CProgression prog;

CPlain2DCamera plain2Dcamera;
CFree3DCamera free3Dcamera;
CAuto3DCamera auto3Dcamera;
CCamera *camera = NULL;

void Move( int stepsToForward, int stepsToLeft, int stepsToUp ){
	CVector3 delta = camera->Move(stepsToForward,stepsToLeft,stepsToUp);
	player.Move(camera->pos,delta);
	CIndex4 i = player.GetCurrentIndex(camera->pos);
	prog.OnItem( *items.ItemAt(i) );
}

//ȥ��һ�ء�����ΪtrueΪ�������أ�����㿪ʼ��Ϊfalse����յ㿪ʼ
void NextLevel( bool toStartPos=true ){
    switch (prog.currentLevel)
    {
		case 1:camera = &plain2Dcamera;break;
		case 2:camera = &plain2Dcamera;break;
		case 3:camera = &plain2Dcamera;break;
		case 4:camera = &free3Dcamera;break;
		case 5:camera = &auto3Dcamera;break;
		case 6:camera = &plain2Dcamera;break;
		default:break;
    }
    maze.LoadData(prog.currentLevel);
    items.LoadData(prog.currentLevel);

    camera->pos = maze.GetInitPosition(toStartPos);
	player.dim = maze.GetInitDim(toStartPos);
	camera->InitCamera();
}

//glut����ƶ����϶��Ļص�����
void MouseMove( int x, int y ){
    static int lastx, lasty;		// ��ʾ�ϴε��øú���ʱ������λ��
    if( lastx * lasty != 0 )		// ���״ε��ã���ִ���ƶ�
	{
		int dx = x-lastx;
		int dy = y-lasty;
		if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // ��ס�Ҽ����ƶ����ƽ��
			Move( 0,-dx/5,-dy/3 );
		else
			camera->Look( -dx/3, -dy/3 ); //����ת���ӽ�

		if( x < 100 || x > 300 ){
			x = 200;
			SetCursorPos( x,y );
		}
		if( y < 100 || y > 300 ){
			y = 200;
			SetCursorPos( x,y );
		}
	}

    lastx = x;
    lasty = y;
}

//glut��갴����������Ӧ����
void MouseDown(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if (button == 3) Move(0,0,5);
	if (button == 4) Move(0,0,-5); 
}

//glut������Ӧ����
void KeyDown(unsigned char key, int a, int b){
	int portal =0;
    switch (key){
    case VK_ESCAPE:     // Esc���˳�����
        glutLeaveMainLoop();
    case 'l':
        glEnable(GL_LIGHTING);
        break;
    case 'k':
        glDisable(GL_LIGHTING);
        break;
    case VK_RETURN: //Enter���л��ؿ�
		portal = maze.LevelPortal(player.GetCurrentIndex(camera->pos));
        if (portal)
        {
			prog.ChangeLevel(portal);
            NextLevel(portal==1);
            return;
        }
		break;
    default:
        break;
    }

    if (key>='0'&&key<='9' && prog.itemLocked[key-'0']!=0 )
    {
		CVector3 position = camera->pos + camera->ori.Normal()/2;
        items.PlaceItem(key,player.GetCurrentIndex(position));
    }
}

//glut��ʱ������ʱˢ�£���ִ���ƶ��Ȳ���
void Timer(int a){
	// ���Ҽ�ͬ��������
	if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && (GetAsyncKeyState(VK_RBUTTON)&0x8000) )
		Move( -1,0,0 );  
	// ֻ�������ǰ��
	if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && !(GetAsyncKeyState(VK_RBUTTON)&0x8000) )
		Move( 1,0,0 );
	// ǰ�� ����
	if ( GetAsyncKeyState('W')&0x8000 )
		Move( 1,0,0 );
	if ( GetAsyncKeyState('S')&0x8000 )
		Move( -1,0,0 );
	//  ����ƽ��
	if ( GetAsyncKeyState('A')&0x8000 )
		Move( 0,1,0 );
	if ( GetAsyncKeyState('D')&0x8000 )
		Move( 0,-1,0 );
	// ����ƽ��
	if ( GetAsyncKeyState(VK_SPACE)&0x8000 )
		Move( 0,0,1 );
	if ( GetAsyncKeyState(VK_SHIFT)|GetAsyncKeyState(VK_CONTROL)&0x8000 )
		Move( 0,0,-1 );

    camera->TimerFunc();
    glutPostRedisplay(); 
    glutTimerFunc( 30, Timer, 0 );
}

//glut��ʾ�ص�����
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->SetCamera();
    Renderer::RenderMaze(maze, player.dim);
    Renderer::Render3DItem(items, player.dim, maze.size, fonts);
	//glRes.DrawArrow();

	//������Ļ��Ե�ķ���ָʾ��ͷ
	glLoadIdentity();
	//glRes.DrawArrow();

    // Hud��Ļ��ӡ���⽨����һ��ģ�͹۲���󣬱��������󣬷����Ӱ��ǰ���LookAt
	char currentItem = *items.ItemAt( player.GetCurrentIndex(camera->pos) );
	Renderer::RenderHudTips(currentItem,fonts, camera->GetType(),prog.currentLevel, 
		(prog.itemLocked[currentItem-'0']<2) );

    glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
	Renderer::InitOpenGL();
	glRes.LoadData(1);
	fonts.LoadData();

    glutPassiveMotionFunc( MouseMove );
    glutMotionFunc( MouseMove );
	glutMouseFunc( MouseDown );
    glutKeyboardFunc( KeyDown );
    glutTimerFunc( 30, Timer, 0 );
    glutDisplayFunc( Display );
	
	NextLevel();
    glutMainLoop();
    return 0;
}
