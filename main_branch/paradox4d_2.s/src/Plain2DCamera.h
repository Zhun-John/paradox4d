#pragma once
#include "camera.h"

//平面Hud摄影机：锁定up向量为z方向，z方向仅能进行垂直升降（类似楼层-电梯，有明显的重力感）
class CPlain2DCamera : public CCamera
{
public:
	CPlain2DCamera(void){};
	virtual ~CPlain2DCamera(void){};
	virtual int GetType(){return 0;}

public:
    virtual CVector3 Move( int stepsToForward, int stepsToLeft, int stepsToUp ){
		CVector3 delta(0,0,0);
		CVector3 left = CVector3::CrossProduct(up,ori).Normal();

		if (stepsToForward!=0)
			delta += CVector3(ori.x,ori.y,0) *moveSpeed *stepsToForward;
		if (stepsToLeft!=0 && abs(stepsToLeft)>abs(stepsToUp) )
		{
			left.z = 0;
			delta += left *moveSpeed *stepsToLeft;
		}
		if (stepsToUp!=0 && abs(stepsToUp)>abs(stepsToLeft) )
			delta.z += moveSpeed *stepsToUp;

		return delta;
	}

    virtual void Look( int stepsToLeft, int stepsToUp ){
		CCamera::Look(stepsToLeft,stepsToUp);

		if( abs(ori.z)>0.99f )
			ori.z = ori.z>0? 0.99f:-0.99f;
		ori.Normalize();
	}
    
};

