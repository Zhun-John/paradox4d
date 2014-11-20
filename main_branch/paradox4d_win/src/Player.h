#pragma once
#include "Maze4D.h"

extern class EMaze4D maze;

class CPlayer
{
public:
    char dim;  //玩家当前所处的维度
    const double manSize;   //玩家的尺寸，即与墙面的最小距离
public:
	CPlayer(void):dim(INDEX4_BASE),manSize(0.2f){};
	~CPlayer(void){};

public:
    //获得当前维度下，某位置对应的迷宫方格坐标
    CIndex4 GetCurrentIndex(const CVector3 &pos){
		CIndex4 i = CIndex4::FromPosition(pos.x,pos.y,pos.z);
		i.d = dim;
		i.d = *maze.DataAt(i);
		return i;
	}

	void Move(CVector3 &pos, CVector3 &delta){
		// 每次移动距离不能超过mansize/2
		if (delta.Length() > manSize/2){
			delta.Normalize();
			delta *= manSize/2;
		}

		// 移动
		pos += delta;

		// 避免穿墙
		CollisionDefend(pos);

		// 换D，核心操作
		CIndex4 i = GetCurrentIndex(pos);
		dim = *(maze.DataAt(i) );
	}

private:
    //避免穿墙
    void CollisionDefend(CVector3 &pos){
		CIndex4 i = CIndex4::FromPosition(pos.x,pos.y,pos.z);
		i.d = dim;

		//当前位置与方块中心的距离
		double disX = (pos.x - i.x) - 0.5;
		double disY = (pos.y - i.y) - 0.5;
		double disZ = (pos.z - i.z) - 0.5;

		//不发生碰撞时，各维度与方块中心的最大距离
		double maxDis = 0.5-manSize;   

		// 若X方向上接近方块边缘，查看X方向上是否与墙相邻。YZ同理
		if ( abs(disX) > maxDis )
			if ( *maze.DataAt((disX>0?i.x+1:i.x-1),i.y,i.z,i.d)=='.' )
				disX = disX>0? maxDis : -maxDis;

		if ( abs(disY) > maxDis )
			if ( *maze.DataAt(i.x,(disY>0?i.y+1:i.y-1),i.z,i.d)=='.' )
				disY = disY>0? maxDis : -maxDis;

		if ( abs(disZ) > maxDis )
			if ( *maze.DataAt(i.x,i.y,(disZ>0?i.z+1:i.z-1),i.d)=='.' )
				disZ = disZ>0? maxDis : -maxDis;

		// 若接近了一个竖直的棱，再判断对角方块是否为墙。YZ/ZX同理
		if ( abs(disX)+abs(disY) > 1-manSize )
			if ( *maze.DataAt((disX>0? i.x+1:i.x-1),(disY>0? i.y+1:i.y-1),i.z,i.d)=='.')
			{
				double backDis = ( abs(disX)+abs(disY) - (1-manSize) ) / 2;
				disX>0 ? disX-=backDis : disX+=backDis;
				disY>0 ? disY-=backDis : disY+=backDis;
			}

		if ( abs(disY)+abs(disZ) > 1-manSize )
			if ( *maze.DataAt(i.x,(disY>0? i.y+1:i.y-1),(disZ>0? i.z+1:i.z-1),i.d)=='.')
			{
				double backDis = ( abs(disY)+abs(disZ) - (1-manSize) ) / 2;
				disY>0 ? disY-=backDis : disY+=backDis;
				disZ>0 ? disZ-=backDis : disZ+=backDis;
			}

		if ( abs(disZ)+abs(disX) > 1-manSize )
			if ( *maze.DataAt((disX>0? i.x+1:i.x-1),i.y,(disZ>0? i.z+1:i.z-1),i.d)=='.')
			{
				double backDis = ( abs(disZ)+abs(disX) - (1-manSize) ) / 2;
				disZ>0 ? disZ-=backDis : disZ+=backDis;
				disX>0 ? disX-=backDis : disX+=backDis;
			}

		//若接近一个角
		if ( abs(disX)+abs(disY)+abs(disZ) > 1.5-manSize )
			if ( *maze.DataAt((disX>0? i.x+1:i.x-1),(disY>0? i.y+1:i.y-1),(disZ>0? i.z+1:i.z-1),i.d)=='.')
			{
				double backDis = ( abs(disY)+abs(disZ) - (1-manSize) ) / 2;
				disX>0 ? disX-=backDis : disX+=backDis;
				disY>0 ? disY-=backDis : disY+=backDis;
				disZ>0 ? disZ-=backDis : disZ+=backDis;
			}

		pos.x = (double)i.x + disX + 0.5;
		pos.y = (double)i.y + disY + 0.5;
		pos.z = (double)i.z + disZ + 0.5;
	}

};

