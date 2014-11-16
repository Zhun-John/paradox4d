#pragma once

//对于第一人称漫游的游戏，Camera即玩家
class CCamera
{
public:
	CCamera(void);
	virtual ~CCamera(void);
    
public:
    //响应鼠标移动和拖动的函数
    virtual void MouseMove(int dx, int dy);

    //定时器，每隔一定时间被调用。主要是移动
    virtual void TimerFunc();

    //初始化摄影机
    void InitCamera(int portal);

    //架设摄影机，即在OpenGL中变换模型视图矩阵
    void SetCamera();

    //获得摄影机当前位置
    void GetPosition(double &posx, double &posy, double &posz);

//////////////////////////////////////////////////////////////////////////
protected:
    double posx, posy, posz;		// 当前位置pos
    double orix, oriy, oriz;		// 当前面对方向ori，始终为单位向量
    double upx, upy, upz;			// 摄影机上方向up，始终为单位向量
    double moveSpeed, turnSpeed;    // 摄影机移动和旋转的速度

protected:
    //移动摄影机
    virtual void Move( int forward, int left, int up )=0;

    //旋转摄影机
    virtual void Look( int left, int up )=0;

    //根据向量ori和up算出当前视角的左方向left，它垂直于up和ori，但并不一定为单位向量
    void GetLeft( double &lx,double &ly,double &lz);

    //将一个向量单位化，使其长度为1.0
    void Normalize( double &x, double &y, double &z );

    //将向量b射影到以a为法向量的平面内
    void Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz );

    // 获得两个向量的夹角，以弧度表示
    double Angle(double ax,double ay,double az, double bx, double by, double bz);

};

