#pragma once

//四维迷宫中的所有物体。每个方格最多放一个物体，每个物体只能放在一个方格中（一对一关系）
class EItem4D
{
public:
    EItem4D(void);
    ~EItem4D(void);

    //初始化某一关的所有物体位置数据
    void Init(int level);

    //渲染所有3D字体
    void RenderAll3DItem();

    //根据当前位置，触发屏幕字体显示
    void Trigger2DRendering();

    //在当前位置放置一个物体
    void PlaceItemHere(char item);

private:
//在本demo描述的四维空间中，每个格子都可能被多个空间看到。物体渲染时必须考虑这种“能看到”的关系
//（这种关系被存在Maze4D类的data中）。对每个物体，必须在能看到它的所有层，都被显示
    char* items;    //四维空间中每个格子的物体，'\0'代表无物体

    //访问四维数组元素值。入参必须合法
    char* ItemAt(int x,int y,int z,char d);

    // 在能看到此物体的所有四维层的相应位置写入此物体的索引item
    void PlaceItem(char item, int x,int y,int z,char d);

};
