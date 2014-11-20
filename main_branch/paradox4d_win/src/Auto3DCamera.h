#pragma once
#include "Free3DCamera.h"

// 3D�Թ�λ��Ӱ������Ӱ�����Ϸ�����Զ�ƥ��������
class CAuto3DCamera : public CFree3DCamera
{
protected:  
	CVector3 goal;		// ƥ�䵽����������������Ӱ���Ϸ�����Զ�����������£
public:
	CAuto3DCamera(void):goal(up){};
	virtual ~CAuto3DCamera(void){};
	virtual int GetType(){return 2;}

public:
    virtual void TimerFunc(){
		up += goal /20;
		up.Normalize();
	}

    virtual void InitCamera()
	{
		CCamera::InitCamera();
		goal = up;
	}

    virtual void Look( int stepsToLeft, int stepsToUp ){
		CCamera::Look(stepsToLeft,stepsToUp);
		ori.Normalize();

		//��ori���ڿ��������Զ��upʱ��Ϊup����ƥ���µ�������
		double angle = CVector3::AngleOf(ori,up);
		if ( angle<M_PI/4 || angle>M_PI*3/4 )
		{
			CVector3 newUp;	//�µ��Ϸ�������
			if (angle>M_PI*3/4)// ��ori����Զ��up����Ϊ��ͷ���µ��Ϸ���Ӧ������ǰ���߷���
				newUp = ori;
			else   // ��ori���ڿ���up����Ϊ̧ͷ���µ��Ϸ���Ӧ������ǰ���ߵĸ�����
				newUp = -ori;

			// ��newUpͶӰ����ֱup��ƽ���ڣ�
			CVector3::Verticalize(newUp,up);
			// �µ��Ϸ���ΪͶӰ���ori�������������ֵ��󣩵�������
			goal.Set(0,0,0 );
			abs(newUp.x)>abs(newUp.z) ? 
				( abs(newUp.x)>abs(newUp.y) ? goal.x=SIGNOF(newUp.x) : goal.y=SIGNOF(newUp.y) ) 
			  : ( abs(newUp.z)>abs(newUp.y) ? goal.z=SIGNOF(newUp.z) : goal.y=SIGNOF(newUp.y) );
		}
	}

};

