#pragma once

class EMaze4D
{
public:
    EMaze4D(void);
    ~EMaze4D(void);

    //��ʼ��ĳһ�ص������Թ���������
    void Init(int level);

    //��Ⱦ�����Թ�
    void Render();

    //����Ӱ���ƶ���ÿ�صĳ�ʼλ��
    void InitCameraPos(double &posx,double &posy,double &posz, int portal);

    //������Ӱ��λ�ã�������ײ��⡣pos_xyzΪ��ǰλ��,d_xyzΪ�ƶ���
    void UpdateCameraPos(double &posx,double &posy,double &posz, double dx,double dy,double dz);

    // �жϵ�ǰ�Ƿ�λ�������յ㣬1�����յ�(ȥ��һ��)��-1�������(ȥ��һ��)��0��������
    int LevelPortal();

    friend class EItem4D;
//////////////////////////////////////////////////////////////////////////
private:
    int mx,my,mz;   // �Թ���ά�ȵĳ���
    int sx,sy,sz;   // ��������start_xyz���ڴ�λ�ÿ���ȥ��һ��
    int ex,ey,ez;   // �յ������end_xyz���ڴ�λ�ÿ���ȥ��һ��
    char md,sd,ed;      // ���ĸ�ά�ȵĳ��ȡ������յ�ĵ���ά���꣬���ַ���ʾ
    char *data;         // ����Թ�����ά����m[d][z][y][x]�����һάx���ַ�������'\0'

    char currentDimension;  //��Ӱ����ǰλ��������ά�ȣ���ǰά�Ȼ�Ӱ���Թ���Ⱦ����˷���Maze���У�
    const double mansize;   //��Ӱ����ǽ�����С���룬����ҵĳߴ�
private:
    //������ά����Ԫ��ֵ����ηǷ��򷵻�ǽ'.'��ָ��
    char* Data(int x,int y,int z,char d);

    //��������Ƿ�λ���Թ��У�
    bool InMaze( int x, int y, int z, char d); 

    //�����Ӱ����ǰλ�ö�Ӧ���Թ���������
    void GetCurrentCoord(int&x,int&y,int&z,char&d);

    //��λ������ת��Ϊ���Թ������е�����
    void PosToIndex(double posx,double posy,double posz,int &ix,int &iy,int &iz);

    //��Ӱ���ƶ������ײ��⣬Ŀǰ�����⴩ǽ
    void CollisionDefend(double &posx,double &posy,double &posz);

};

