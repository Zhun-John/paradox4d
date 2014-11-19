#include "global.h"
#include "Free3DCamera.h"
#include "Maze4D.h"

extern EMaze4D maze;


CFree3DCamera::CFree3DCamera(void)
{
}


CFree3DCamera::~CFree3DCamera(void)
{
}

void CFree3DCamera::Move( int forward, int left, int up )
{
    double dx=0,dy=0,dz=0;

    if (forward!=0)
    {
        dx += orix *moveSpeed *forward;
        dy += oriy *moveSpeed *forward;
        dz += oriz *moveSpeed *forward;
    }
    if (left!=0)
    {
        double lx,ly,lz;
        GetLeft(lx,ly,lz);
        dx += lx *moveSpeed *left;
        dy += ly *moveSpeed *left;
        dz += lz *moveSpeed *left;
    }
    if (up!=0)
    {
        dx += upx *moveSpeed *up;
        dy += upy *moveSpeed *up;
        dz += upz *moveSpeed *up;
    }

    maze.UpdateCameraPos(posx,posy,posz,dx,dy,dz);
}

void CFree3DCamera::Look( int left, int up )
{
    double lx, ly, lz;
    GetLeft( lx,ly,lz);
    orix += lx *turnSpeed *left;
    oriy += ly *turnSpeed *left;
    oriz += lz *turnSpeed *left;
    Normalize( orix, oriy, oriz );

    orix += upx *turnSpeed * up;
    oriy += upy *turnSpeed * up;
    oriz += upz *turnSpeed * up;
    Normalize( orix, oriy, oriz );

    Verticalize(orix,oriy,oriz, upx,upy,upz);
    Normalize(upx,upy,upz);
}
