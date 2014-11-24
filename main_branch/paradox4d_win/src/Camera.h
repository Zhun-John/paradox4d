#pragma once
#include "global.h"
#include "Vector3.h"

class CCamera
{
public:
    CVector3 pos;		// ��ǰλ��pos
	CVector3 ori;		// ��ǰ���߷���ori��ʼ��Ϊ��λ����
    CVector3 up;		// ��Ӱ���Ϸ���up��ʼ��Ϊ��λ����
    double moveSpeed, turnSpeed;	// ��Ӱ���ƶ�����ת���ٶ�
public:
	CCamera(void):moveSpeed(0.05f),turnSpeed(0.015f){};
	virtual ~CCamera(void){};

	//�����Ӱ��(���ӽ�)�����͡�
	virtual int GetType()=0;
    
public:
    //��ʱ����ÿ��һ��ʱ�䱻����
    virtual void TimerFunc(){}

    //��ʼ����Ӱ��
    virtual void InitCamera(){
		ori = CVector3(0.0f,1.0f,0.0f);
		up = CVector3(0.0f,0.0f,1.0f);
	}

    //������Ӱ��������OpenGL�б任ģ����ͼ����
	void SetCamera(){
		glMatrixMode( GL_PROJECTION );// projection matrix is lens of camera
		glLoadIdentity();
		gluPerspective( 100.0, 1.5, 0.05f, 9999.0f );
		glMatrixMode( GL_MODELVIEW );// modelview matrix is position of camera
		gluLookAt(pos.x, pos.y, pos.z, pos.x+ori.x, pos.y+ori.y, pos.z+ori.z, up.x, up.y, up.z );
	}

	//�ƶ���Ӱ��
    virtual CVector3 Move( int stepsToForward, int stepsToLeft, int stepsToUp )=0;

    //��ת��Ӱ��
	virtual void Look( int stepsToLeft, int stepsToUp ){
		ori += CVector3::CrossProduct(up,ori).Normal() *turnSpeed *stepsToLeft;
		ori += up *turnSpeed *stepsToUp;
	}

};

