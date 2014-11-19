#pragma once

//���ڵ�һ�˳����ε���Ϸ��Camera�����
class CCamera
{
public:
	CCamera(void);
	virtual ~CCamera(void);
    
public:
    //��Ӧ����ƶ����϶��ĺ���
    virtual void MouseMove(int dx, int dy);

    //��ʱ����ÿ��һ��ʱ�䱻���á���Ҫ���ƶ�
    virtual void TimerFunc();

    //��ʼ����Ӱ��
    void InitCamera(int portal);

    //������Ӱ��������OpenGL�б任ģ����ͼ����
    void SetCamera();

    //�����Ӱ����ǰλ��
    void GetPosition(double &posx, double &posy, double &posz);

//////////////////////////////////////////////////////////////////////////
protected:
    double posx, posy, posz;		// ��ǰλ��pos
    double orix, oriy, oriz;		// ��ǰ��Է���ori��ʼ��Ϊ��λ����
    double upx, upy, upz;			// ��Ӱ���Ϸ���up��ʼ��Ϊ��λ����
    double moveSpeed, turnSpeed;    // ��Ӱ���ƶ�����ת���ٶ�

protected:
    //�ƶ���Ӱ��
    virtual void Move( int forward, int left, int up )=0;

    //��ת��Ӱ��
    virtual void Look( int left, int up )=0;

    //��������ori��up�����ǰ�ӽǵ�����left������ֱ��up��ori��������һ��Ϊ��λ����
    void GetLeft( double &lx,double &ly,double &lz);

    //��һ��������λ����ʹ�䳤��Ϊ1.0
    void Normalize( double &x, double &y, double &z );

    //������b��Ӱ����aΪ��������ƽ����
    void Verticalize( double ax,double ay,double az, double &bx,double &by,double &bz );

    // ������������ļнǣ��Ի��ȱ�ʾ
    double Angle(double ax,double ay,double az, double bx, double by, double bz);

};

