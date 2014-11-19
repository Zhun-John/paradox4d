#include "global.h"
#include "Plain2DCamera.h"
#include "Maze4D.h"

extern EMaze4D maze;

CPlain2DCamera::CPlain2DCamera(void)
{
}


CPlain2DCamera::~CPlain2DCamera(void)
{
}

void CPlain2DCamera::Move( int forward, int left, int up  )
{
    double dx=0,dy=0,dz=0;

    if (forward!=0)
    {
        dx += orix *moveSpeed *forward;
        dy += oriy *moveSpeed *forward;
    }
    if (left!=0)
    {
        double lx,ly,lz;
        GetLeft(lx,ly,lz);
        dx += lx *moveSpeed *left;
        dy += ly *moveSpeed *left;
    }
    if (up!=0)
    {
        dz += moveSpeed *up;
    }

    maze.UpdateCameraPos(posx,posy,posz,dx,dy,dz);
}

void CPlain2DCamera::Look( int left, int up ){
    double lx, ly, lz;
    GetLeft( lx,ly,lz);
    orix += lx *turnSpeed *left;
    oriy += ly *turnSpeed *left;
    oriz += lz *turnSpeed *left;
    Normalize( orix, oriy, oriz );

    oriz += turnSpeed * up;
    if( abs(oriz)>0.99f )
    {
        oriz = oriz>0? 0.99f:-0.99f;
    }
    Normalize( orix, oriy, oriz );
}
