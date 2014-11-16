#pragma once
#include "Free3DCamera.h"

// 3D自归位摄影机：摄影机的上方向会自动匹配坐标轴
class CAuto3DCamera : public CFree3DCamera
{
protected:  
	CVector3 goal;		// 匹配到的坐标轴向量。摄影机上方向会自动朝此向量靠拢
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

		//当ori过于靠近或过于远离up时，为up向量匹配新的坐标轴
		double angle = CVector3::AngleOf(ori,up);
		if ( angle<M_PI/4 || angle>M_PI*3/4 )
		{
			CVector3 newUp;	//新的上方向向量
			if (angle>M_PI*3/4)// 若ori过于远离up，即为低头，新的上方向应靠近当前视线方向
				newUp = ori;
			else   // 若ori过于靠近up，即为抬头，新的上方向应靠近当前视线的负方向
				newUp = -ori;

			// 将newUp投影到垂直up的平面内，
			CVector3::Verticalize(newUp,up);
			// 新的上方向即为投影后的ori向量最靠近（绝对值最大）的坐标轴
			goal.Set(0,0,0 );
			abs(newUp.x)>abs(newUp.z) ? 
				( abs(newUp.x)>abs(newUp.y) ? goal.x=SIGNOF(newUp.x) : goal.y=SIGNOF(newUp.y) ) 
			  : ( abs(newUp.z)>abs(newUp.y) ? goal.z=SIGNOF(newUp.z) : goal.y=SIGNOF(newUp.y) );
		}
	}

};

