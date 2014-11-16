#pragma once
#include "global.h"
#include "Vector3.h"

class CCamera
{
public:
    CVector3 pos;		// 当前位置pos
	CVector3 ori;		// 当前视线方向ori，始终为单位向量
    CVector3 up;		// 摄影机上方向up，始终为单位向量
    double moveSpeed, turnSpeed;	// 摄影机移动和旋转的速度
public:
	CCamera(void):moveSpeed(0.05f),turnSpeed(0.015f){};
	virtual ~CCamera(void){};

	//获得摄影机(即视角)的类型。
	virtual int GetType()=0;
    
public:
    //定时器，每隔一定时间被调用
    virtual void TimerFunc(){}

    //初始化摄影机
    virtual void InitCamera(){
		ori = CVector3(0.0f,1.0f,0.0f);
		up = CVector3(0.0f,0.0f,1.0f);
	}

    //架设摄影机，即在OpenGL中变换模型视图矩阵
    void SetCamera(double aspect){
		glLoadIdentity();
		gluPerspective( 110.0f, aspect, 0.05f, 9999.0f );
		gluLookAt(pos.x, pos.y, pos.z, pos.x+ori.x, pos.y+ori.y, pos.z+ori.z, up.x, up.y, up.z );
	}

	//移动摄影机
    virtual CVector3 Move( int stepsToForward, int stepsToLeft, int stepsToUp )=0;

    //旋转摄影机
	virtual void Look( int stepsToLeft, int stepsToUp ){
		ori += CVector3::CrossProduct(up,ori).Normal() *turnSpeed *stepsToLeft;
		ori += up *turnSpeed *stepsToUp;
	}

};

