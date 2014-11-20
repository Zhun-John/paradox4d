#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"
#include "glResouce.h"

extern class CglResouce glRes;

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
		if (data!=NULL)
		{
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
    //初始化某一关的所有迷宫地形数据
    void InitData(int level);

    //渲染整个迷宫
    void Render(char dim){
		//此处遍历不宜改为CIndex4.Iterate，因其内有对坐标细节的改动
		for( int iz=0; iz<size.z; iz++ )
		 for( int iy=0; iy<size.y; iy++ )
		  for( int ix=0; ix<size.x-1; ix++ )
			//仅对非墙的方格，即玩家可见区域，进行绘制
			if (*DataAt(ix,iy,iz,dim)!='.')
			{
				glPushMatrix();
				glTranslated( (ix+0.5), (iy+0.5), (iz+0.5) );
				glColor3d(1,1,1);

				// Y方向的墙
				if( *DataAt(ix,iy-1,iz,dim)=='.' ){
					glCallList( glRes.LwallY );
				}
				if( *DataAt(ix,iy+1,iz,dim)=='.' ){
					glRotated( 180, 0.0f,0.0f,1.0f );
					glCallList( glRes.LwallY );
					glRotated( -180, 0.0f,0.0f,1.0f );
				}

				// Z方向的天花板、地板
				if( *DataAt(ix,iy,iz-1,dim)=='.' ){
					glCallList( glRes.Lground );
				}
				if( *DataAt(ix,iy,iz+1,dim)=='.' ){
					glCallList( glRes.Lceiling );
				}

				// X方向的墙
				if( *DataAt(ix-1,iy,iz,dim)=='.' ){
					glCallList( glRes.LwallX );
				}
				if( *DataAt(ix+1,iy,iz,dim)=='.' ){
					glRotated( 180, 0.0f,0.0f,1.0f );
					glCallList( glRes.LwallX );
					glRotated( -180, 0.0f,0.0f,1.0f );
				}

				glPopMatrix();
			}
	}

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

