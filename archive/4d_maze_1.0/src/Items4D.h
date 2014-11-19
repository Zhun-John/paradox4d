#pragma once
#include "global.h"
#include "Maze4D.h"

//四维空间中的一个三维物体图层
//每个格子只能放一个物体，若需要多个物体，则使用此类的多个子类各自渲染
class EItems4D
{
public:
    EItems4D(void);
    virtual ~EItems4D(void);

    //在能看到此物体的所有位置写入此物体的索引item
    void PlaceItem(char item, int x,int y,int z,char d);

    void Init();
    void Render();
    
    char* ItemAt(int x,int y,int z,char d);

    virtual void RenderAt(int x,int y,int z,char d)=0;

private:
//在本demo描述的四维空间中，每个格子都可能被多个空间看到。物体渲染时必须考虑这种“能看到”的关系
    //（这种关系被存在Maze4D类的data中）。对每个物体，必须在能看到它的所有层，都被显示
    char* items; //所有物体在四维空间中的位置

};

