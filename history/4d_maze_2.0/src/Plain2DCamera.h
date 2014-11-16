#pragma once
#include "camera.h"

//ƽ��2D��Ӱ��������up����Ϊz����z������ܽ��д�ֱ����������¥��-���ݣ������Ե������У�
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

