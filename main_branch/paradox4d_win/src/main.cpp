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

//去下一关。参数为true为正常过关，从起点开始；为false则从终点开始
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

//glut鼠标移动、拖动的回调函数
void MouseMove( int x, int y ){
    static int lastx, lasty;		// 表示上次调用该函数时，鼠标的位置
    if( lastx * lasty != 0 )		// 非首次调用，才执行移动
	{
		int dx = x-lastx;
		int dy = y-lasty;
		if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // 按住右键，移动鼠标平移
			Move( 0,-dx/5,-dy/3 );
		else
			camera->Look( -dx/3, -dy/3 ); //否则，转动视角

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

//glut鼠标按键、滚轮响应函数
void MouseDown(int button, int state, int x, int y)
{
	// Wheel reports as button 3(scroll up) and button 4(scroll down)
	if (button == 3) Move(0,0,5);
	if (button == 4) Move(0,0,-5); 
}

//glut键盘响应函数
void KeyDown(unsigned char key, int a, int b){
	int portal =0;
    switch (key){
    case VK_ESCAPE:     // Esc键退出程序
        glutLeaveMainLoop();
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
    camera->SetCamera();
    Renderer::RenderMaze(maze, player.dim);
    Renderer::Render3DItem(items, player.dim, maze.size, fonts);
	//glRes.DrawArrow();

	//绘制屏幕边缘的方向指示箭头
	glLoadIdentity();
	//glRes.DrawArrow();

    // Hud屏幕打印另外建立了一个模型观察矩阵，必须放在最后，否则会影响前面的LookAt
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
