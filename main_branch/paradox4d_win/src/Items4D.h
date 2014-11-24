#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"
#include "Maze4D.h"

extern class EMaze4D maze;

//四维迷宫中的所有物体。每个方格最多放一个物体，每个物体只能放在一个方格中（一对一关系）
class EItem4D
{
private:
    char* data;    //四维空间中每个格子的物体，'\0'代表无物体
public:
	EItem4D(void):data(NULL){};
	~EItem4D(void){
		if (data!=NULL){
			free(data);
			data=NULL;
		}
    }
    
	//访问四维数组元素值。入参必须合法
    char* ItemAt(int x,int y,int z,char d){
		return ItemAt( CIndex4(x,y,z,d) );
	}
	char* ItemAt(const CIndex4 &i){
		return data + i.OffsetInside(maze.size);
	}

public:
	//载入某一关的所有物体位置数据
	void LoadData(int level);

    // 在能看到此物体的所有四维层的相应位置，写入此物体item
    void PlaceItem(char item, int x,int y,int z,char d){
		PlaceItem(item, CIndex4(x,y,z,d) );
	}
	void PlaceItem(char item, const CIndex4 &here){
		//若此位置不在此层
		if (*(maze.DataAt(here)) != here.d)
			return;

		//若此位置已经有物体，且不是可擦除的物体（汉字一到九的标记）
		char *itemHere = ItemAt(here);
		if ( *itemHere!='\0' && !(*itemHere>='0'&&*itemHere<='9') )
			return;//则不擦除此物体，直接返回

		//每个物体只能放在一个方格中，先将整个空间中的此物体清空，随后重新放置
		CIndex4 i;
		i.Reset();
		do{
			itemHere = ItemAt(i);
			if (*itemHere==item)
				*itemHere = '\0';
		}while ( !i.IterateInside(maze.size) );

		//在所有能看到此物体的四维层里的相应三维位置上，写入此物体的索引
		i.Reset(0,0,0,here.d);
		CIndex4 size = maze.size;
		size.d = here.d+1;
		do{
			//对d层空间，其上的ix,iy,iz位置属于dim层空间
			char dim = *(maze.DataAt(i));
			//dim层空间看到的物体位置
			char see = *(maze.DataAt(here.x,here.y,here.z, dim));
			if (see == here.d)
				//在dim层空间的相应位置放置物体item
				*ItemAt(here.x,here.y,here.z, dim) = item;
		}while ( !i.IterateInside(size) );
	}

};
