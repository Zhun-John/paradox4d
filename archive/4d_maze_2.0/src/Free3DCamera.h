#pragma once
#include "camera.h"

// 全自由3D摄影机：ori和up始终垂直，摄影机始终绕up或left轴旋转，若要绕视线自转，鼠标画圆即可
class CFree3DCamera :
    public CCamera
{
public:
    CFree3DCamera(void);
    virtual ~CFree3DCamera(void);

protected:
    virtual void Move( int forward, int left, int up );
    virtual void Look( int left, int up );
};

