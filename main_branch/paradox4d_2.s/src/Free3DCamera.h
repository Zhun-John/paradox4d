#pragma once
#include "camera.h"

// ȫ����3D��Ӱ����ori��upʼ�մ�ֱ����Ӱ��ʼ����up��left����ת��
class CFree3DCamera : public CCamera
{
public:
    CFree3DCamera(void){};
    virtual ~CFree3DCamera(void){};
	virtual int GetType(){return 1;}

public:
    virtual CVector3 Move(int stepsToForward, int stepsToLeft, int stepsToUp){
		CVector3 delta(0,0,0);
		CVector3 left = CVector3::CrossProduct(up,ori).Normal();

		if (stepsToForward!=0)
			delta += ori *moveSpeed *stepsToForward;
		if (stepsToLeft!=0)
			delta += left *moveSpeed *stepsToLeft;
		if (stepsToUp!=0)
			delta += up *moveSpeed *stepsToUp;

		return delta;
	}

    virtual void Look( int stepsToLeft, int stepsToUp )
	{
		CCamera::Look(stepsToLeft,stepsToUp);
		ori.Normalize();

		CVector3::Verticalize(up,ori);
		up.Normalize();
	}
};

