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
        MessageBox(NULL,"�������ˣ�","WaHoo!",MB_OK);
        currentLevel++;
        InitLevel();
        return;
    }
    else {
        MessageBox(NULL,"��ͨ���˱���Ϸ��ȫ��3�ع�ϲ��","UaHoo!",MB_OK);
        exit(0);
    }
}

//////////////////////////////////////////////////////////////////////////
void ResetCursor( int &x, int &y ){
    // ������굽����Ļ��Ե��û�����ߣ���ʱ��Ҫ�����λ����Ϊ��Ļ����
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
    // ����ƶ����϶�ʱ�ĺ���
    static int lastx, lasty;		// ��ʾ�ϴε��øú���ʱ������λ��
    if( lastx * lasty == 0 ){		// ˵���ǵ�һ�ε��ú���
        lastx = x; lasty = y;
        return;
    }

    if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // ��ס�Ҽ����ƶ����ƽ��
    {
        levelComplete = camera.Move( 0,-(x-lastx)/3.0f,-(y-lasty)/4.0f );  
    }
    else
    {
        camera.Look( (x-lastx)/3.0f, -(y-lasty)/3.0f ); //����ת���ӽ�
    }

    lastx = x;
    lasty = y;
    ResetCursor( lastx, lasty );
    glutPostRedisplay();	
}

void KeyDown(unsigned char key, int a, int b){
    switch (key){
    case VK_ESCAPE:     // Esc���˳�����
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
    // ÿ��һ��ʱ��ͱ����õĺ�������Ҫ���������ƶ����ٶȣ�ʹ���������ܲ�ͬ�Ļ����ϲ����仯
    if ( GetAsyncKeyState(VK_LBUTTON)&0x8000 )
    {
        if( GetAsyncKeyState(VK_RBUTTON)&0x8000 ){   
            levelComplete = camera.Move( -1,0,0 );  // ���Ҽ�ͬ������
        }
        else
        {
            levelComplete = camera.Move( 1,0,0 );   // ֻ�����ǰ��
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

    // 2D��Ļ��ӡ���⽨����һ��ģ�͹۲���󣬱��������󣬷����Ӱ��ǰ���LookAt
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
