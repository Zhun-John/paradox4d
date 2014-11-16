#pragma once
#include "global.h"

class EMaze4D
{
public:
    EMaze4D(void);
    ~EMaze4D(void);
    
    void Init(int level);
    void Render();

    void InitPos(double &posx,double &posy,double &posz);
    void UpdatePos(double &posx,double &posy,double &posz, double ix,double iy,double iz );
    void GetCurrentCoord(int&x,int&y,int&z,char&d);

    //������Ӱ��λ�ã��жϵ�ǰ�ؿ��Ƿ�ͨ��
    bool LevelComplete(double posx,double posy,double posz);

    friend class EItems4D;
//////////////////////////////////////////////////////////////////////////
private:
    int mx,my,mz;   // �Թ���ά�ȵĳ���
    int sx,sy,sz;   // ��ʼλ�õ�����
    char md,sd;         // ���ĸ�ά�ȵĳ��Ⱥ���ʼλ�ã��ô�д��ĸ��ʾ���糤��Ϊ2��md=='C'
    char *data;         // ����Թ�����ά����m[d][z][y][x]�����һάx���ַ�����'\0'

    char currentDimension;  //��Ӱ����ǰλ��������ά�ȣ���ǰά�Ȼ�Ӱ���Թ���Ⱦ����˷���Maze���У�
    const double mansize;   //��Ӱ����ǽ�����С����
private:
    void ReadFromFile(int level);

    void CollisionDefend(double &posx,double &posy,double &posz);

    //��λ������ת��Ϊ���Թ������е�����
    void PosToIndex(double posx,double posy,double posz,int &ix,int &iy,int &iz);
    
    bool InMaze( int x, int y, int z, char d);

    //������ά����Ԫ��ֵ����ηǷ��򷵻�ǽ'.'������
    char* Data(int x,int y,int z,char d);

    //�ж��Թ������е�ĳ��ֵ�Ƿ�Ϸ�
    bool DataLegal(char data);
};

