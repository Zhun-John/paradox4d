#pragma once

class EMaze4D
{
public:
    EMaze4D(void);
    ~EMaze4D(void);

    //初始化某一关的所有迷宫地形数据
    void Init(int level);

    //渲染整个迷宫
    void Render();

    //将摄影机移动到每关的初始位置
    void InitCameraPos(double &posx,double &posy,double &posz, int portal);

    //更新摄影机位置，包含碰撞检测。pos_xyz为当前位置,d_xyz为移动量
    void UpdateCameraPos(double &posx,double &posy,double &posz, double dx,double dy,double dz);

    // 判断当前是否位于起点或终点，1代表终点(去下一关)，-1代表起点(去上一关)，0代表其它
    int LevelPortal();

    friend class EItem4D;
//////////////////////////////////////////////////////////////////////////
private:
    int mx,my,mz;   // 迷宫各维度的长度
    int sx,sy,sz;   // 起点的坐标start_xyz，在此位置可以去上一关
    int ex,ey,ez;   // 终点的坐标end_xyz，在此位置可以去下一关
    char md,sd,ed;      // 第四个维度的长度、起点和终点的第四维坐标，用字符表示
    char *data;         // 存放迷宫的四维数组m[d][z][y][x]，最后一维x是字符串，有'\0'

    char currentDimension;  //摄影机当前位置所处的维度（当前维度会影响迷宫渲染，因此放在Maze类中）
    const double mansize;   //摄影机与墙面的最小距离，即玩家的尺寸
private:
    //访问四维数组元素值，入参非法则返回墙'.'的指针
    char* Data(int x,int y,int z,char d);

    //这个方格是否位于迷宫中？
    bool InMaze( int x, int y, int z, char d); 

    //获得摄影机当前位置对应的迷宫方格坐标
    void GetCurrentCoord(int&x,int&y,int&z,char&d);

    //将位置坐标转换为在迷宫矩阵中的索引
    void PosToIndex(double posx,double posy,double posz,int &ix,int &iy,int &iz);

    //摄影机移动后的碰撞检测，目前仅避免穿墙
    void CollisionDefend(double &posx,double &posy,double &posz);

};

