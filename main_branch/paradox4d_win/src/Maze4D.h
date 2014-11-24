#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"

class EMaze4D
{
//在本demo描述的四维空间中，每个格子都可能被多个空间看到。物体渲染时必须考虑这种“能看到”的关系
//（这种关系被存在Maze4D类的data中）。
public:
	CIndex4 size;		// 迷宫尺寸（作为字符串的x维度已额外+1）
	CIndex4 start,end;	// 迷宫起点和终点的坐标
    char *data;         // 存放迷宫的四维数组m[d][z][y][x]，最后一维x是字符串，有'\0'

public:
    EMaze4D(void):data(NULL){};
    ~EMaze4D(void){
		if (data!=NULL){
			free(data);
			data=NULL;
		}
	}
    //访问四维数组元素值，入参非法则返回墙'.'的指针
    char* DataAt(int x,int y,int z,char d){
		return DataAt( CIndex4(x,y,z,d) );
	}
    char* DataAt(const CIndex4 &i){
		static char wall='.';
		if (!i.IsInside(size))
			return &wall;
		return data + i.OffsetInside(size);
	}

public:
    //载入某一关的所有迷宫地形数据
    void LoadData(int level);

    //获得每关的初始位置及维度。参数为true返回起点，为false返回终点
	CVector3 GetInitPosition(bool startPosition){
		if (startPosition) 
			return CVector3(start.x+0.5f,start.y+0.5f,start.z+0.5f);
		else
			return CVector3(end.x+0.5f,end.y+0.5f,end.z+0.5f);
	}
	char GetInitDim(bool startPosition){
		if (startPosition) 
			return start.d;
		else
			return end.d;
	}

    // 判断当前是否位于起点或终点，1代表终点(去下一关)，-1代表起点(去上一关)，0代表其它
    int LevelPortal(const CIndex4 &i){
		if (i==start)
			return -1;
		if (i==end)
			return 1;
		return 0;
	}

};

