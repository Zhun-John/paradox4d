#pragma once
#include "camera.h"

//平面2D摄影机：锁定up向量为z方向，z方向仅能进行垂直升降（类似楼层-电梯，有明显的重力感）
class CPlain2DCamera :
    public CCamera
{
public:
    CPlain2DCamera(void);
    virtual ~CPlain2DCamera(void);

protected:
    virtual void Move( int forward, int left, int up );
    virtual void Look( int left, int up );
    
};

