#include "global.h"
#include "Info.h"
#include "Camera.h"
#include "Maze4D.h"
#include "glResouce.h"

CglResouce glRes;
EMaze4D maze;
EInfo info;
CCamera camera;

int currentLevel=1, levelSum=3;
bool levelComplete=false;

void InitLevel(){
    levelComplete = false;

    maze.Init(currentLevel);
    glRes.Init(currentLevel);
    info.Init(currentLevel);

    camera.InitCamera();
}

void NextLevel()
{
    if( currentLevel < levelSum ){
        MessageBox(NULL,"您过关了！","WaHoo!",MB_OK);
        currentLevel++;
        InitLevel();
        return;
    }
    else {
        MessageBox(NULL,"您通过了本游戏的全部3关恭喜！","UaHoo!",MB_OK);
        exit(0);
    }
}

//////////////////////////////////////////////////////////////////////////
void ResetCursor( int &x, int &y ){
    // 由于鼠标到了屏幕边缘就没法再走，此时需要把鼠标位置设为屏幕中心
    if( x < 100 || x > WINDOW_WID - 100 ){
        x = WINDOW_WID / 2;
        SetCursorPos( x,y );
    }
    if( y < 100 || y > WINDOW_HEI - 100 ){
        y = WINDOW_HEI / 2;
        SetCursorPos( x,y );
    }
}

void MouseMove( int x, int y ){
    // 鼠标移动和拖动时的函数
    static int lastx, lasty;		// 表示上次调用该函数时，鼠标的位置
    if( lastx * lasty == 0 ){		// 说明是第一次调用函数
        lastx = x; lasty = y;
        return;
    }

    if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // 按住右键，移动鼠标平移
    {
        levelComplete = camera.Move( 0,-(x-lastx)/3.0f,-(y-lasty)/4.0f );  
    }
    else
    {
        camera.Look( (x-lastx)/3.0f, -(y-lasty)/3.0f ); //否则，转动视角
    }

    lastx = x;
    lasty = y;
    ResetCursor( lastx, lasty );
    glutPostRedisplay();	
}

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
    default:
        break;
    }
    if (key>='0'&&key<='9')
    {
        int ix,iy,iz;
        char id;
        maze.GetCurrentCoord(ix,iy,iz,id);
        info.PlaceItem(key,ix,iy,iz,id);
    }
    glutPostRedisplay();
}

void Timer(int a){
    // 每隔一定时间就被调用的函数，主要用来控制移动的速度，使得它在性能不同的机器上不会大变化
    if ( GetAsyncKeyState(VK_LBUTTON)&0x8000 )
    {
        if( GetAsyncKeyState(VK_RBUTTON)&0x8000 ){   
            levelComplete = camera.Move( -1,0,0 );  // 左右键同按后退
        }
        else
        {
            levelComplete = camera.Move( 1,0,0 );   // 只按左键前进
        }
    }

    glutPostRedisplay(); 

    glutTimerFunc( 15, Timer, 0 );
}

void Display(void)
{
    if (levelComplete)
    {
        NextLevel();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.SetCamera();
    maze.Render();

    // 2D屏幕打印另外建立了一个模型观察矩阵，必须放在最后，否则会影响前面的LookAt
    info.Render();

    glutSwapBuffers();
    return;
}

//////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glRes.InitGL();
    glutPassiveMotionFunc( MouseMove );
    glutMotionFunc( MouseMove );
    glutKeyboardFunc( KeyDown );
    glutTimerFunc( 1, Timer, 0 );
    glutDisplayFunc( Display );

    InitLevel();
    glutMainLoop();
    return 0;
}
