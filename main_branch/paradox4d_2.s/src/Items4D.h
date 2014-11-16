#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"

#include "Maze4D.h"
#include "Tips.h"

extern class EMaze4D maze;
extern class ETips tips;

//四维迷宫中的所有物体。每个方格最多放一个物体，每个物体只能放在一个方格中（一对一关系）
class EItem4D
{
private:
    char* data;    //四维空间中每个格子的物体，'\0'代表无物体
public:
	EItem4D(void):data(NULL){};
	~EItem4D(void){
		if (data!=NULL)
		{
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
    //初始化某一关的所有物体位置数据
    void Init(int level){
		if (data) free(data);
		int dataSize = maze.size.Capacity();
		data = (char*)malloc( dataSize );
		if (!data) exit(0);

		memset(data,'\0',dataSize);
		PlaceItem('{',maze.start);
		PlaceItem('}',maze.end);

		if (level==1)
		{
			PlaceItem('a',1,2,0,'A');
			PlaceItem('1',4,2,0,'F');
			PlaceItem('2',4,2,0,'I');
			PlaceItem('3',2,1,0,'H');
		}
		else if (level==2)
		{
			PlaceItem('4',2,2,0,'G');
			PlaceItem('Z',2,3,0,'T');
		}
		else if (level==3)
		{
			PlaceItem('a',2,2,4,'A');
			PlaceItem('b',2,2,6,'A');
			PlaceItem('c',2,2,7,'A');
			PlaceItem('d',0,0,7,'A');
		}
		else if (level==4)
		{
			PlaceItem('b',3,2,2,'A');
			PlaceItem('c',0,2,0,'A');
			PlaceItem('d',4,4,4,'A');
		}
		else if (level==5)
		{
			PlaceItem('a',4,5,3,'A');
			PlaceItem('b',2,1,5,'A');
/*	//原立柱关的物品
			PlaceItem('a',1,2,0,'A');
			PlaceItem('b',5,3,0,'I');
			PlaceItem('c',5,1,0,'F');
			PlaceItem('d',3,1,0,'H');
			PlaceItem('e',1,1,0,'H');*/
		}

	}

    //渲染所有3D字体
    void RenderAll3DItem(char dim){
		CIndex4 i(0,0,0,dim);
		CIndex4 size(maze.size);
		size.d = dim+1;
		do{
			glPushMatrix();
			glTranslated( (i.x+0.5), (i.y+0.5), (i.z+0.5) );
			glRotated(90,1,0,0);

			tips.Render3DTips( *ItemAt(i));

			glPopMatrix();
		}while( !i.IterateInside(size) );
	}

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
