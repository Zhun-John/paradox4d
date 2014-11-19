#include "global.h"
#include "Tips.h"
#include "Items4D.h"
#include "Camera.h"
#include "Maze4D.h"
#include "glResouce.h"
#include "Plain2DCamera.h"
#include "Free3DCamera.h"
#include "Auto3DCamera.h"

#define WINDOW_WID 800		// ��Ļ���
#define WINDOW_HEI 600		// ��Ļ�߶�

CglResouce glRes;
EMaze4D maze;
ETips tips;
EItem4D items;

CPlain2DCamera plain2Dcamera;
CFree3DCamera free3Dcamera;
CAuto3DCamera auto3Dcamera;
CCamera *camera = NULL;

int currentLevel=1, levelSum=5;     //��ǰ�ؿ����ؿ�����

//��ʼ���ؿ���portalΪ1�����������أ�������һ�ص��յ��л�����һ����㣬-1Ϊ����
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

//��ʼ��OpenGL
void InitGL( void )
{
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize( WINDOW_WID, WINDOW_HEI );
    glutInitWindowPosition( 0,0 );
    glutCreateWindow( "3D�Թ�" );
    glutFullScreen();
    glutSetCursor( GLUT_CURSOR_NONE );

    glEnable(GL_TEXTURE_2D); // ��������ӳ��
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

    glRes.BuildFont("����",40,40,0,0,0);
    glRes.LoadGLTextures(1);
    glRes.BuildWall();
}

//glut����ƶ����϶��Ļص�����
void MouseMove( int x, int y ){
    static int lastx, lasty;		// ��ʾ�ϴε��øú���ʱ������λ��
    if( lastx * lasty == 0 ){		// ˵���ǵ�һ�ε��ú���
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

//glut������Ӧ����
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
    case VK_RETURN: //Enter���л��ؿ�
        if (maze.LevelPortal()!=0)
        {
            currentLevel += maze.LevelPortal();
            if (currentLevel>0 && currentLevel<=levelSum)
            {
                InitLevel(maze.LevelPortal());
                return;
            }
            else //�����ڵ�һ���������һ���յ㰴�س����˳�����
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

//glut��ʱ������ʱˢ�£���ִ���ƶ��Ȳ���
void Timer(int a){
    camera->TimerFunc();    //�ڴ�ִ���ƶ��ɱ�֤�ٶ��ȶ������ܻ�������Ӱ��
    glutPostRedisplay(); 
    glutTimerFunc( 15, Timer, 0 );
}

//glut��ʾ�ص�����
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->SetCamera();
    maze.Render();
    items.RenderAll3DItem();

    // 2D��Ļ��ӡ���⽨����һ��ģ�͹۲���󣬱��������󣬷����Ӱ��ǰ���LookAt
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
