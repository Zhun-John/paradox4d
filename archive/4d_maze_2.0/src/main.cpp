#include "global.h"
#include "Tips.h"
#include "Items4D.h"
#include "Camera.h"
#include "Maze4D.h"
#include "glResouce.h"
#include "Plain2DCamera.h"
#include "Free3DCamera.h"
#include "Auto3DCamera.h"

#define WINDOW_WID 800		// 屏幕宽度
#define WINDOW_HEI 600		// 屏幕高度

CglResouce glRes;
EMaze4D maze;
ETips tips;
EItem4D items;

CPlain2DCamera plain2Dcamera;
CFree3DCamera free3Dcamera;
CAuto3DCamera auto3Dcamera;
CCamera *camera = NULL;

int currentLevel=1, levelSum=5;     //当前关卡、关卡总数

//初始化关卡，portal为1代表正常过关，即从上一关的终点切换到下一关起点，-1为反向
void InitLevel( int portal=1 ){
    maze.Init(currentLevel);
    //glRes.Init(currentLevel);
    items.Init(currentLevel);
    tips.Init(currentLevel);

    switch (currentLevel)
    {
    case 1:camera = &plain2Dcamera;break;
    case 2:camera = &plain2Dcamera;break;
    case 3:camera = &free3Dcamera;break;
    case 4:camera = &auto3Dcamera;break;
    case 5:camera = &plain2Dcamera;break;
    case 6:camera = &plain2Dcamera;break;
    default:break;
    }
    camera->InitCamera(portal);
}

//初始化OpenGL
void InitGL( void )
{
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( WINDOW_WID, WINDOW_HEI );
    glutInitWindowPosition( 0,0 );
    glutCreateWindow( "3D迷宫" );
    glutFullScreen();
    glutSetCursor( GLUT_CURSOR_NONE );

    glEnable(GL_TEXTURE_2D); // 启用纹理映射
    glShadeModel(GL_SMOOTH); // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black Background
    glClearDepth(1.0f); // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
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

    glRes.BuildFont("宋体",40,40,0,0,0);
    glRes.LoadGLTextures(1);
    glRes.BuildWall();
}

//glut鼠标移动、拖动的回调函数
void MouseMove( int x, int y ){
    static int lastx, lasty;		// 表示上次调用该函数时，鼠标的位置
    if( lastx * lasty == 0 ){		// 说明是第一次调用函数
        lastx = x; lasty = y;
        return;
    }

    camera->MouseMove(x-lastx, y-lasty);

    if( x < 100 || x > WINDOW_WID - 100 ){
        x = WINDOW_WID/2;
        SetCursorPos( x,y );
    }
    if( y < 100 || y > WINDOW_HEI - 100 ){
        y = WINDOW_HEI/2;
        SetCursorPos( x,y );
    }

    lastx = x;
    lasty = y;
}

//glut键盘响应函数
void KeyDown(unsigned char key, int a, int b){
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
        if (maze.LevelPortal()!=0)
        {
            currentLevel += maze.LevelPortal();
            if (currentLevel>0 && currentLevel<=levelSum)
            {
                InitLevel(maze.LevelPortal());
                return;
            }
            else //否则，在第一关起点或最后一关终点按回车，退出程序
            {
                exit(0);
            }
        }
        break;
    default:
        break;
    }

    if (key>='0'&&key<='9')
    {
        items.PlaceItemHere(key);
    }
}

//glut定时器，定时刷新，并执行移动等操作
void Timer(int a){
    camera->TimerFunc();    //在此执行移动可保证速度稳定，不受机器性能影响
    glutPostRedisplay(); 
    glutTimerFunc( 15, Timer, 0 );
}

//glut显示回调函数
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->SetCamera();
    maze.Render();
    items.RenderAll3DItem();

    // 2D屏幕打印另外建立了一个模型观察矩阵，必须放在最后，否则会影响前面的LookAt
    items.Trigger2DRendering();

    glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    InitGL();

    glutPassiveMotionFunc( MouseMove );
    glutMotionFunc( MouseMove );
    glutKeyboardFunc( KeyDown );
    glutTimerFunc( 15, Timer, 0 );
    glutDisplayFunc( Display );

    InitLevel();
    glutMainLoop();
    return 0;
}
