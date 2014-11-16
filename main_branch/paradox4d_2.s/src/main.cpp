#include "global.h"
#include "Tips.h"
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

#define WINDOW_WID 800		// 屏幕宽度
#define WINDOW_HEI 600		// 屏幕高度

#pragma comment(lib,"GLAUX.LIB")
#pragma comment(lib,"GLU32.LIB")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glut.lib")

CglResouce glRes;
EMaze4D maze;
ETips tips;
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

//初始化关卡，portal为1代表正常过关，即从上一关的终点切换到下一关起点，-1为反向
void InitLevel( int portal=1 ){
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
    maze.InitData(prog.currentLevel);
    items.Init(prog.currentLevel);

    camera->pos = maze.GetInitPosition(portal==1);
	player.dim = maze.GetInitDim(portal==1);
	camera->InitCamera();
}

//glut鼠标移动、拖动的回调函数
void MouseMove( int x, int y ){
    static int lastx, lasty;		// 表示上次调用该函数时，鼠标的位置
    if( lastx * lasty != 0 )		// 非首次调用，才执行移动
	{
		int dx = x-lastx;
		int dy = y-lasty;
		if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // 按住右键，移动鼠标平移
			Move( 0,-dx/5.0f,-dy/3.0f );
		else
			camera->Look( -dx/3.0f, -dy/3.0f ); //否则，转动视角

		if( x < 100 || x > WINDOW_WID - 100 ){
			x = WINDOW_WID/2;
			SetCursorPos( x,y );
		}
		if( y < 100 || y > WINDOW_HEI - 100 ){
			y = WINDOW_HEI/2;
			SetCursorPos( x,y );
		}
	}

    lastx = x;
    lasty = y;
}

//glut键盘响应函数
void KeyDown(unsigned char key, int a, int b){
	int portal =0;
    switch (key){
    case VK_ESCAPE:     // Esc键退出程序
        exit(0);
    case 'l':
        glEnable(GL_LIGHTING);
        break;
    case 'k':
        glDisable(GL_LIGHTING);
        break;
    case VK_RETURN: //Enter键切换关卡
		portal = maze.LevelPortal(player.GetCurrentIndex(camera->pos));
        if (portal)
        {
			prog.ChangeLevel(portal);
            InitLevel(portal);
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

//glut定时器，定时刷新，并执行移动等操作
void Timer(int a){
	// 左右键同按：后退
	if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && (GetAsyncKeyState(VK_RBUTTON)&0x8000) )
		Move( -1,0,0 );  
	// 只按左键：前进
	if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && !(GetAsyncKeyState(VK_RBUTTON)&0x8000) )
		Move( 1,0,0 );
	// 前进 后退
	if ( GetAsyncKeyState('W')&0x8000 )
		Move( 1,0,0 );
	if ( GetAsyncKeyState('S')&0x8000 )
		Move( -1,0,0 );
	//  左右平移
	if ( GetAsyncKeyState('A')&0x8000 )
		Move( 0,1,0 );
	if ( GetAsyncKeyState('D')&0x8000 )
		Move( 0,-1,0 );
	// 上下平移
	if ( GetAsyncKeyState(VK_SPACE)&0x8000 )
		Move( 0,0,1 );
	if ( GetAsyncKeyState(VK_SHIFT)|GetAsyncKeyState(VK_CONTROL)&0x8000 )
		Move( 0,0,-1 );

    camera->TimerFunc();
    glutPostRedisplay(); 
    glutTimerFunc( 30, Timer, 0 );
}

//glut显示回调函数
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->SetCamera(WINDOW_WID/WINDOW_HEI);
    maze.Render(player.dim);
    items.RenderAll3DItem(player.dim);
	//glRes.DrawArrow();

	//绘制屏幕边缘的方向指示箭头
	glLoadIdentity();
	//glRes.DrawArrow();

    // Hud屏幕打印另外建立了一个模型观察矩阵，必须放在最后，否则会影响前面的LookAt
	CIndex4 currentIndex = player.GetCurrentIndex(camera->pos);
	char currentItem = *(items.ItemAt(currentIndex));
	tips.RenderHudTips(currentItem,camera->GetType(),prog.currentLevel, 
		(prog.itemLocked[currentItem-'0']<2) );

    glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glRes.InitOpenGL(WINDOW_WID,WINDOW_HEI);

    glutPassiveMotionFunc( MouseMove );
    glutMotionFunc( MouseMove );
    glutKeyboardFunc( KeyDown );
    glutTimerFunc( 30, Timer, 0 );
    glutDisplayFunc( Display );
	
    tips.Init();
    InitLevel();
    glutMainLoop();
    return 0;
}
