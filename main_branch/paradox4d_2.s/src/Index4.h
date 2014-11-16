#pragma once
#include <math.h>

#define INDEX4_BASE ('A')

// һ���Թ������4d���꣨xά����Ϊ�ַ����������ڱ�����+1��
class CIndex4
{//----���Ҵ�δ��������������Ĵ����������֡�@2014.10.17
public:
	int x,y,z;	//���Թ������е�xyz����
	char d;		//����ά�ȣ����ַ���ʾ

public:
	CIndex4(int X=0,int Y=0,int Z=0,char D=INDEX4_BASE)
		:x(X),y(Y),z(Z),d(D)
	{};
	CIndex4(const CIndex4 &other)
		:x(other.x),y(other.y),z(other.z),d(other.d)
	{};
	~CIndex4(void){};

	//��λ��ת��Ϊ�Թ����ꡣ��dΪĬ��ֵ
	static CIndex4 FromPosition(double posX, double posY, double posZ){
		return CIndex4( floor(posX), floor(posY), floor(posZ) );
	}
	void Reset(int X=0,int Y=0,int Z=0, char D=INDEX4_BASE){
		x=X; y=Y; z=Z; d=D;
	}
	
public:
	//�� �Ե�ǰ����Ϊ�Ͻ����ά�ռ� ��ռ�õ��ֽ���
	int Capacity()const{
		return x * y * z * (d-INDEX4_BASE);
	}
	//��ǰ�����Ƿ��� ���½�Ϊ[0,size)����ά�ռ� ֮��
	bool IsInside(const CIndex4 &size)const{
		return x>=0 && x<size.x-1
			&& y>=0 && y<size.y 
			&& z>=0 && z<size.z
			&& d>=INDEX4_BASE && d<size.d;
	}
	//��ǰ��������� ���½�Ϊ[0,size)����ά�ռ� ��ƫ����
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
	//�õ�ǰ������ ���½�Ϊ[0,size)����ά�ռ� �ڱ���������trueΪ����ɱ�����falseΪδ���
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

