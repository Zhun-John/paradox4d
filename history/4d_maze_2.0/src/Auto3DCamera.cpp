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

    //��ori���ڿ��������Զ��upʱ��Ϊup����ƥ���µ�������
    double angle = Angle(orix,oriy,oriz, upx,upy,upz);
    if ( angle<M_PI/4 || angle>M_PI*3/4 )
    {
        gx=0; gy=0; gz=0;
        double ox, oy, oz;
        if (angle>M_PI*3/4)  // ��ori����Զ��up����Ϊ��ͷ���µ��Ϸ���Ӧ������ǰ���߷���
        {
            ox=orix; oy=oriy; oz=oriz;
        }
        else   // ��ori���ڿ���up����Ϊ̧ͷ���µ��Ϸ���Ӧ������ǰ���ߵĸ�����
        {
            ox=-orix; oy=-oriy; oz=-oriz;
        }

        // ��oriͶӰ����ֱup��ƽ���ڣ��µ��Ϸ���ΪͶӰ���ori�������������ֵ��󣩵�������
        Verticalize(upx,upy,upz, ox,oy,oz);
        abs(ox)>abs(oz) ? 
            ( abs(ox)>abs(oy) ? gx=SIGNOF(ox) : gy=SIGNOF(oy) ) 
            : ( abs(oz)>abs(oy) ? gz=SIGNOF(oz) : gy=SIGNOF(oy) );
    }
}
