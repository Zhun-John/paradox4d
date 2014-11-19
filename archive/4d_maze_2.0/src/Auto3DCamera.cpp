#include "global.h"
#include "Auto3DCamera.h"
#include "Maze4D.h"

extern EMaze4D maze;



CAuto3DCamera::CAuto3DCamera(void)
    :gx(upx),gy(upy),gz(upz)
{
}


CAuto3DCamera::~CAuto3DCamera(void)
{
}

void CAuto3DCamera::TimerFunc()
{
    CCamera::TimerFunc();

    upx += gx/30;
    upy += gy/30;
    upz += gz/30;
    Normalize(upx,upy,upz);
}

void CAuto3DCamera::Look( int left, int up )
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

    //当ori过于靠近或过于远离up时，为up向量匹配新的坐标轴
    double angle = Angle(orix,oriy,oriz, upx,upy,upz);
    if ( angle<M_PI/4 || angle>M_PI*3/4 )
    {
        gx=0; gy=0; gz=0;
        double ox, oy, oz;
        if (angle>M_PI*3/4)  // 若ori过于远离up，即为低头，新的上方向应靠近当前视线方向
        {
            ox=orix; oy=oriy; oz=oriz;
        }
        else   // 若ori过于靠近up，即为抬头，新的上方向应靠近当前视线的负方向
        {
            ox=-orix; oy=-oriy; oz=-oriz;
        }

        // 将ori投影到垂直up的平面内，新的上方向即为投影后的ori向量最靠近（绝对值最大）的坐标轴
        Verticalize(upx,upy,upz, ox,oy,oz);
        abs(ox)>abs(oz) ? 
            ( abs(ox)>abs(oy) ? gx=SIGNOF(ox) : gy=SIGNOF(oy) ) 
            : ( abs(oz)>abs(oy) ? gz=SIGNOF(oz) : gy=SIGNOF(oy) );
    }
}
