#pragma once
#include "Free3DCamera.h"

// 3D自归位摄影机：摄影机的上方向会自动匹配坐标轴
class CAuto3DCamera :
    public CFree3DCamera
{
public:
    CAuto3DCamera(void);
    virtual ~CAuto3DCamera(void);

    virtual void TimerFunc();

protected:
    virtual void Look( int left, int up );

protected:
    double gx,gy,gz;    // 匹配到的坐标轴向量。摄影机上方向会自动朝此向量靠拢
};

