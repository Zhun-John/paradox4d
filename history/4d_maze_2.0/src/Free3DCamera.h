#pragma once
#include "camera.h"

// ȫ����3D��Ӱ����ori��upʼ�մ�ֱ����Ӱ��ʼ����up��left����ת����Ҫ��������ת����껭Բ����
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

