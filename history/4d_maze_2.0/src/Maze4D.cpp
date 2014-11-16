#include "global.h"
#include "Maze4D.h"
#include "glResouce.h"
#include "Camera.h"

extern class CglResouce glRes;
extern class CCamera *camera;

EMaze4D::EMaze4D(void)
    :mansize(0.2f),data(NULL)
{
}

EMaze4D::~EMaze4D()
{
    if (data)
    {
        free(data);
        data=NULL;
    }
}

void EMaze4D::PosToIndex( double posx,double posy,double posz,int &ix,int &iy,int &iz )
{
    ix = floor(posx);
    iy = floor(posy);
    iz = floor(posz);
}

bool EMaze4D::InMaze( int x, int y, int z, char d )
{
    return (x>=0 && y>=0 && z>=0 && d>='A') && (x<mx && y<my && z<mz && d<md);
}

char* EMaze4D::Data( int x,int y,int z,char d )
{
    static char wall='.';
    if (!InMaze(x,y,z,d))
    {
        return &wall;
    }
    return (data + x + (mx+1) * ( y + my * (z + mz * (d-'A') ) ) );
}

void EMaze4D::CollisionDefend( double &posx,double &posy,double &posz)
{
    int ix,iy,iz;
    PosToIndex(posx,posy,posz,ix,iy,iz);

    //当前位置与方块中心的距离
    double disX = (posx - ix) - 0.5;
    double disY = (posy - iy) - 0.5;
    double disZ = (posz - iz) - 0.5;
    
    // 若X方向上接近方块边缘，查看X方向上是否与墙相邻。YZ同理
    double maxDis = 0.5-mansize;   //不发生碰撞时，各维度与方块中心的最大距离
    if ( abs(disX) > maxDis )
    {
        if ( *Data((disX>0?ix+1:ix-1),iy,iz,currentDimension)=='.' )
        {
            disX = disX>0? maxDis : -maxDis;
        }
    }
    if ( abs(disY) > maxDis )
    {
        if ( *Data(ix,(disY>0?iy+1:iy-1),iz,currentDimension)=='.' )
        {
            disY = disY>0? maxDis : -maxDis;
        }
    }
    if ( abs(disZ) > maxDis )
    {
        if ( *Data(ix,iy,(disZ>0?iz+1:iz-1),currentDimension)=='.' )
        {
            disZ = disZ>0? maxDis : -maxDis;
        }
    }

    // 若接近了一个竖直的棱，再判断对角方块是否为墙。YZ/ZX同理
    if ( abs(disX)+abs(disY) > 1-mansize )
    {
        if ( *Data((disX>0? ix+1:ix-1),(disY>0? iy+1:iy-1),iz,currentDimension)=='.')
        {
            double backDis = ( abs(disX)+abs(disY) - (1-mansize) ) / 2;
            disX>0 ? disX-=backDis : disX+=backDis;
            disY>0 ? disY-=backDis : disY+=backDis;
        }
    }
    if ( abs(disY)+abs(disZ) > 1-mansize )
    {
        if ( *Data(ix,(disY>0? iy+1:iy-1),(disZ>0? iz+1:iz-1),currentDimension)=='.')
        {
            double backDis = ( abs(disY)+abs(disZ) - (1-mansize) ) / 2;
            disY>0 ? disY-=backDis : disY+=backDis;
            disZ>0 ? disZ-=backDis : disZ+=backDis;
        }
    }
    if ( abs(disZ)+abs(disX) > 1-mansize )
    {
        if ( *Data((disX>0? ix+1:ix-1),iy,(disZ>0? iz+1:iz-1),currentDimension)=='.')
        {
            double backDis = ( abs(disZ)+abs(disX) - (1-mansize) ) / 2;
            disZ>0 ? disZ-=backDis : disZ+=backDis;
            disX>0 ? disX-=backDis : disX+=backDis;
        }
    }

    //若接近一个角
    if ( abs(disX)+abs(disY)+abs(disZ) > 1.5-mansize )
    {
        if ( *Data((disX>0? ix+1:ix-1),(disY>0? iy+1:iy-1),(disZ>0? iz+1:iz-1),currentDimension)=='.')
        {
            double backDis = ( abs(disY)+abs(disZ) - (1-mansize) ) / 2;
            disX>0 ? disX-=backDis : disX+=backDis;
            disY>0 ? disY-=backDis : disY+=backDis;
            disZ>0 ? disZ-=backDis : disZ+=backDis;
        }
    }

    posx = ix + disX + 0.5;
    posy = iy + disY + 0.5;
    posz = iz + disZ + 0.5;
}

//////////////////////////////////////////////////////////////////////////
void EMaze4D::Render(){

    for( int iz=0; iz<mz; iz++ )
        for( int iy=0; iy<my; iy++ )
            for( int ix=0; ix<mx; ix++ )
                if (*Data(ix,iy,iz,currentDimension)!='.')//仅对非墙的方格，即玩家可见区域，进行绘制
                {
                    glPushMatrix();
                    glTranslated( (ix+0.5), (iy+0.5), (iz+0.5) );
                    glColor3d(1,1,1);

                    // Y方向的墙
                    if( *Data(ix,iy-1,iz,currentDimension)=='.' ){
                        glCallList( glRes.LwallY );
                    }
                    if( *Data(ix,iy+1,iz,currentDimension)=='.' ){
                        glRotated( 180, 0.0f,0.0f,1.0f );
                        glCallList( glRes.LwallY );
                        glRotated( -180, 0.0f,0.0f,1.0f );
                    }

                    // Z方向的天花板、地板
                    if( *Data(ix,iy,iz-1,currentDimension)=='.' ){
                        glCallList( glRes.Lground );
                    }
                    if( *Data(ix,iy,iz+1,currentDimension)=='.' ){
                        glCallList( glRes.Lceiling );
                    }

                    // X方向的墙
                    if( *Data(ix-1,iy,iz,currentDimension)=='.' ){
                        glCallList( glRes.LwallX );
                    }
                    if( *Data(ix+1,iy,iz,currentDimension)=='.' ){
                        glRotated( 180, 0.0f,0.0f,1.0f );
                        glCallList( glRes.LwallX );
                        glRotated( -180, 0.0f,0.0f,1.0f );
                    }

                    glPopMatrix();
                }
}

void EMaze4D::InitCameraPos( double &posx,double &posy,double &posz, int portal )
{
    if (portal==1)  // 从终点传送过来的，应到达下一关的起点
    {
        posx = sx+0.5f;
        posy = sy+0.5f;
        posz = sz+0.5f;
        currentDimension = sd;
    }
    if (portal==-1)// 反之，应到达上一关的终点
    {
        posx = ex+0.5f;
        posy = ey+0.5f;
        posz = ez+0.5f;
        currentDimension = ed;
    }
}

void EMaze4D::UpdateCameraPos( double &posx,double &posy,double &posz, double dx,double dy,double dz )
{
    //每次移动距离不能超过mansize/2
    double distance = sqrt(dx*dx+dy*dy+dz*dz);
    if (distance > mansize/2)
    {
        dx = dx / distance * mansize/2;
        dy = dy / distance * mansize/2;
        dz = dz / distance * mansize/2;
    }

    posx += dx;
    posy += dy;
    posz += dz;

    CollisionDefend(posx,posy,posz);
    
    int ix,iy,iz;
    PosToIndex(posx,posy,posz,ix,iy,iz);
    currentDimension = *Data(ix,iy,iz,currentDimension);// 换D，核心操作
}

int EMaze4D::LevelPortal()
{
    int ix,iy,iz;
    char id;
    GetCurrentCoord(ix,iy,iz,id);
    if (ix==sx && iy==sy && iz==sz && id==sd)
    {
        return -1;
    }
    if (ix==ex && iy==ey && iz==ez && id==ed)
    {
        return 1;
    }
    return 0;
}

void EMaze4D::GetCurrentCoord( int&x,int&y,int&z,char&d )
{
    double posx,posy,posz;
    camera->GetPosition(posx,posy,posz);
    PosToIndex(posx,posy,posz,x,y,z);
    d = currentDimension;
}
