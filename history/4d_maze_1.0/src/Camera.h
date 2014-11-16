#pragma once
#include "global.h"

//对于第一人称漫游的游戏，Camera即玩家
class CCamera
{
public:
	CCamera(void);
	~CCamera(void);
    
public:
    //返回值：移动后的位置是否过关
    bool Move( int forward, int left, int up );
    void Look( int x, int y );

    void InitCamera();
    void SetCamera();

    void GetPosition(double&posx,double&posy,double&posz);

//////////////////////////////////////////////////////////////////////////
private:
    double posx, posy, posz;		// 当前位置
    double orix, oriy, oriz;		// 当前面对方向,该向量为单位向量
    double upx, upy, upz;			// 照相机上方，该向量为单位向量 // 本版本内up永远为z轴正向
    
private:
    void GetLeft( double &lx,double &ly,double &lz);

	/// 将向量b射影到以a为法向量的平面内
    void Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz );

    void Normalize( double &x, double &y, double &z );
};

