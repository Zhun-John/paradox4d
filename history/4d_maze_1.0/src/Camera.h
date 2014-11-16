#pragma once
#include "global.h"

//���ڵ�һ�˳����ε���Ϸ��Camera�����
class CCamera
{
public:
	CCamera(void);
	~CCamera(void);
    
public:
    //����ֵ���ƶ����λ���Ƿ����
    bool Move( int forward, int left, int up );
    void Look( int x, int y );

    void InitCamera();
    void SetCamera();

    void GetPosition(double&posx,double&posy,double&posz);

//////////////////////////////////////////////////////////////////////////
private:
    double posx, posy, posz;		// ��ǰλ��
    double orix, oriy, oriz;		// ��ǰ��Է���,������Ϊ��λ����
    double upx, upy, upz;			// ������Ϸ���������Ϊ��λ���� // ���汾��up��ԶΪz������
    
private:
    void GetLeft( double &lx,double &ly,double &lz);

	/// ������b��Ӱ����aΪ��������ƽ����
    void Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz );

    void Normalize( double &x, double &y, double &z );
};

