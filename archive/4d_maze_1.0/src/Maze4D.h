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

    //根据摄影机位置，判断当前关卡是否通过
    bool LevelComplete(double posx,double posy,double posz);

    friend class EItems4D;
//////////////////////////////////////////////////////////////////////////
private:
    int mx,my,mz;   // 迷宫各维度的长度
    int sx,sy,sz;   // 起始位置的坐标
    char md,sd;         // 第四个维度的长度和起始位置，用大写字母表示，如长度为2则md=='C'
    char *data;         // 存放迷宫的四维数组m[d][z][y][x]，最后一维x是字符串有'\0'

    char currentDimension;  //摄影机当前位置所处的维度（当前维度会影响迷宫渲染，因此放在Maze类中）
    const double mansize;   //摄影机与墙面的最小距离
private:
    void ReadFromFile(int level);

    void CollisionDefend(double &posx,double &posy,double &posz);

    //将位置坐标转换为在迷宫矩阵中的索引
    void PosToIndex(double posx,double posy,double posz,int &ix,int &iy,int &iz);
    
    bool InMaze( int x, int y, int z, char d);

    //访问四维数组元素值，入参非法则返回墙'.'的引用
    char* Data(int x,int y,int z,char d);

    //判断迷宫矩阵中的某个值是否合法
    bool DataLegal(char data);
};

