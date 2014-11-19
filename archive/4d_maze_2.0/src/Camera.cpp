#include "global.h"
#include "Camera.h"
#include "glResouce.h"
#include "Maze4D.h"

extern EMaze4D maze;

CCamera::CCamera(void)
    :moveSpeed(0.02f),turnSpeed(0.015f)
{
}

CCamera::~CCamera(void)
{
}

void CCamera::Normalize( double &x, double &y, double &z )
{
	double r;
	r = sqrt( x*x + y*y + z*z );
	x /= r;
	y /= r;
	z /= r;
}

void CCamera::GetLeft( double &lx,double &ly,double &lz){
    lx = upy*oriz - upz*oriy;
    ly = upz*orix - upx*oriz;
    lz = upx*oriy - upy*orix;
}

//////////////////////////////////////////////////////////////////////////

void CCamera::MouseMove( int dx, int dy )
{
    if ( GetAsyncKeyState(VK_RBUTTON)&0x8000 ) // 按住右键，移动鼠标平移
    {
        Move( 0,-dx/3.0f,-dy/4.0f );  
    }
    else
    {
        Look( -dx/3.0f, -dy/3.0f ); //否则，转动视角
    }

}

void CCamera::TimerFunc()
{
    if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && (GetAsyncKeyState(VK_RBUTTON)&0x8000) )
    {   
        Move( -1,0,0 );  // 左右键同按：后退
    }
    if ( (GetAsyncKeyState(VK_LBUTTON)&0x8000) && !(GetAsyncKeyState(VK_RBUTTON)&0x8000) )
    {
        Move( 1,0,0 );   // 只按左键：前进
    }
}

void CCamera::SetCamera()
{
    glLoadIdentity();
    gluPerspective( 90.0f, 1.3f, 0.05f, 9999.0f );
    gluLookAt(posx, posy, posz, posx+orix, posy+oriy, posz+oriz, upx, upy, upz );
}

void CCamera::InitCamera(int portal)
{
    maze.InitCameraPos(posx,posy,posz,portal);

    orix = 0.0f;
    oriy = 1.0f;
    oriz = 0.0f;
    
    upx = 0.0f;
    upy = 0.0f;
    upz = 1.0f;
}

void CCamera::GetPosition( double&posx,double&posy,double&posz )
{
    posx = this->posx;
    posy = this->posy;
    posz = this->posz;
}

double CCamera::Angle( double ax,double ay,double az, double bx, double by, double bz )
{
    double dot = ax*bx + ay*by + az*bz;
    double la = sqrt(ax*ax + ay*ay + az*az);
    double lb = sqrt(bx*bx + by*by + bz*bz);
    return acos(dot/la/lb);
}

void CCamera::Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz )
{
    double cos;
    cos = ax*bx + ay*by + az*bz;
    bx -= ax*cos;
    by -= ay*cos;
    bz -= az*cos;
}
