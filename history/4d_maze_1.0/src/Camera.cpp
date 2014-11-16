#include "Camera.h"
#include "glResouce.h"
#include "Maze4D.h"

extern EMaze4D maze;

CCamera::CCamera(void)
{
}

CCamera::~CCamera(void)
{
}

void CCamera::Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz )
{
	double cos;
	cos = ax*bx + ay*by + az*bz;
	bx -= ax*cos;
	by -= ay*cos;
	bz -= az*cos;
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
    /// 根据向量ori和向量up算出当前视角的左方向。左方向不一定是单位向量
    lx = upy*oriz - upz*oriy;
    ly = upz*orix - upx*oriz;
    lz = upx*oriy - upy*orix;
}

//////////////////////////////////////////////////////////////////////////
bool CCamera::Move( int forward, int left, int up  )
{
    double speed=0.02;
    double dx=0,dy=0,dz=0;

    if (forward!=0)
    {
        double rate = oriz * oriz * abs(oriz);
        dx += orix *(1-rate) *speed *forward;
        dy += oriy *(1-rate) *speed *forward;
        dz += oriz *rate *speed *forward;
    }
    if (left!=0)
    {
        double lx,ly,lz;
        GetLeft(lx,ly,lz);
        dx += lx *speed *left;
        dy += ly *speed *left;
    }
    if (up!=0)
    {
        dz += speed *up;
    }

    maze.UpdatePos(posx,posy,posz,dx,dy,dz);

    return maze.LevelComplete(posx,posy,posz);
}

void CCamera::Look( int right, int up ){
    double speed=0.015f;
    double leftx, lefty, leftz;
    GetLeft( leftx,lefty,leftz);
    orix += leftx *speed *-right;
    oriy += lefty *speed *-right;
    oriz += leftz *speed *-right;
    Normalize( orix, oriy, oriz );

    oriz += speed * up;
    if( abs(oriz)>0.99f )
    {
        oriz = oriz>0? 0.99f:-0.99f;
    }
    Normalize( orix, oriy, oriz );
}

void CCamera::SetCamera()
{
    glLoadIdentity();
    gluPerspective( 90.0f, 1.3f, 0.05f, 9999.0f );
    gluLookAt(posx, posy, posz, posx+orix, posy+oriy, posz+oriz, upx, upy, upz );
}

void CCamera::InitCamera()
{
    maze.InitPos(posx,posy,posz);

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
