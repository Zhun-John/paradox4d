#pragma once
#include <math.h>

#define INDEX4_BASE ('A')

// 一个迷宫方格的4d坐标（x维度作为字符串，在其内被额外+1）
class CIndex4
{//----“我从未想象过，如此美妙的代码会出自我手”@2014.10.17
public:
	int x,y,z;	//在迷宫数组中的xyz坐标
	char d;		//第四维度，以字符表示

public:
	CIndex4(int X=0,int Y=0,int Z=0,char D=INDEX4_BASE)
		:x(X),y(Y),z(Z),d(D)
	{};
	CIndex4(const CIndex4 &other)
		:x(other.x),y(other.y),z(other.z),d(other.d)
	{};
	~CIndex4(void){};

	//将位置转换为迷宫坐标。其d为默认值
	static CIndex4 FromPosition(double posX, double posY, double posZ){
		return CIndex4( floor(posX), floor(posY), floor(posZ) );
	}
	void Reset(int X=0,int Y=0,int Z=0, char D=INDEX4_BASE){
		x=X; y=Y; z=Z; d=D;
	}
	
public:
	//求 以当前坐标为上界的四维空间 所占用的字节数
	int Capacity()const{
		return x * y * z * (d-INDEX4_BASE);
	}
	//当前坐标是否处于 上下界为[0,size)的四维空间 之内
	bool IsInside(const CIndex4 &size)const{
		return x>=0 && x<size.x-1
			&& y>=0 && y<size.y 
			&& z>=0 && z<size.z
			&& d>=INDEX4_BASE && d<size.d;
	}
	//求当前坐标相对于 上下界为[0,size)的四维空间 的偏移量
	int OffsetInside(const CIndex4 &size)const{
		int offset=0;
		offset += d-INDEX4_BASE;
		offset *= size.z;
		offset += z;
		offset *= size.y;
		offset += y;
		offset *= size.x;
		offset += x;
		return offset;
	}
	//用当前坐标在 上下界为[0,size)的四维空间 内遍历。返回true为已完成遍历，false为未完成
	bool IterateInside(const CIndex4 &size){
		if( !IsInside(size) )
			return true;
		x++;
		if (x >= size.x-1)
		{
			x=0;
			y++;
			if (y >= size.y)
			{
				y=0;
				z++;
				if(z >= size.z)
				{
					z=0;
					d++;
					if (d >= size.d)
						return true;
				}
			}
		}
		return false;
	}

public:
	const CIndex4 operator=( const CIndex4 &other ){
		x=other.x;	y=other.y;	z=other.z; d=other.d;
		return *this;
	}
	bool operator==( const CIndex4 &other )const{
		return x==other.x && y==other.y && z==other.z && d==other.d;
	}

};

