#pragma once
#include <math.h>

class CVector3
{
public:	// 变量
	double x,y,z;	// 向量的三个分量

public:	// 构造、析构
	CVector3( double X=1.0f, double Y=0.0f, double Z=0.0f )
		:x(X),y(Y),z(Z)
	{};
	CVector3( const CVector3& other )
		:x(other.x),y(other.y),z(other.z)
	{};
	~CVector3() {};

	void Set( double X, double Y, double Z ){
		x=X;	y=Y;	z=Z;
	}

public:
	// 向量长度
	double Length()const{
		return sqrt(x*x+y*y+z*z);
	}
	// 向量单位化
	void Normalize(){ 
		double len = this->Length();
		x/=len;
		y/=len;
		z/=len;
	}			
	// 求法向量（同方向的单位向量）
	CVector3 Normal()const{
		CVector3 v(*this);
		v.Normalize();
		return v;
	}	

public:
	// 向量求和
	static CVector3 Add( const CVector3 &a, const CVector3 &b ){
		return CVector3( a.x+b.x, a.y+b.y, a.z+b.z );
	}
	// 向量数乘
	static CVector3 Multiply( const CVector3 &a, const double &b ){
		return CVector3( a.x*b, a.y*b, a.z*b );
	}
	// 两向量夹角的余弦值
	static double CosOf( const CVector3 &a, const CVector3 &b ){
		return DotProduct(a,b) / a.Length() / b.Length();
	}		
	// 两向量的夹角，以弧度计算
	static double AngleOf( const CVector3 &a, const CVector3 &b ){
		return acos(CosOf(a,b));
	}	
	// 向量点积
	static double DotProduct( const CVector3 &a, const CVector3 &b ){
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}		
	// 向量叉积
	static CVector3 CrossProduct( const CVector3 &left, const CVector3 &right){
		return CVector3(left.y*right.z - left.z*right.y,
						left.z*right.x - left.x*right.z,
						left.x*right.y - left.y*right.x);
	}
	// a在向量b上的投影
	static CVector3 Project( const CVector3& a, const CVector3& b ){
		// 点积除以b的长度，得到a在b上的投影长度，再乘以b的方向向量即可
		return DotProduct(a,b) / b.Length() * b.Normal();
	}
	// 将v投影到以norm为法线的平面上
	static void Verticalize( CVector3& v, const CVector3& norm ){
		v -= Project(v,norm);
	}

public:
	CVector3 operator-()const{
		return CVector3( -x, -y, -z );
	}
	const CVector3 operator=( const CVector3 &other ){
		x=other.x;	y=other.y;	z=other.z;
		return *this;
	}

	const CVector3 operator+( const CVector3 &other )const{
		return Add(*this,other);
	}
	const CVector3 operator-( const CVector3 &other )const{
		return Add(*this,-other);
	}
	const CVector3 operator*( const double d )const{
		return Multiply(*this,d);
	}
	const CVector3 operator/( const double d )const{
		return Multiply(*this,1.0f/d);
	}

	const CVector3 operator+=( const CVector3 &other ){
		return *this = Add(*this,other);
	}
	const CVector3 operator-=( const CVector3 &other ){
		return *this = Add(*this,-other);
	}
	const CVector3 operator*=( const double d ){
		return *this = Multiply(*this,d);
	}
	const CVector3 operator/=( const double d ){
		return *this = Multiply(*this,1.0f/d);
	}
public:	
	// 实现 数值乘以向量 的运算
	friend CVector3 operator*( const double b, const CVector3 &other ){
		return CVector3::Multiply(other,b);
	}
};
