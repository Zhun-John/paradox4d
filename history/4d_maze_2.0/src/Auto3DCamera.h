#pragma once
#include "Free3DCamera.h"

// 3D�Թ�λ��Ӱ������Ӱ�����Ϸ�����Զ�ƥ��������
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
    double gx,gy,gz;    // ƥ�䵽����������������Ӱ���Ϸ�����Զ�����������£
};

