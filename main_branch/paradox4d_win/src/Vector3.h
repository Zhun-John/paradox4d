#pragma once
#include <math.h>

class CVector3
{
public:	// ����
	double x,y,z;	// ��������������

public:	// ���졢����
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
	// ��������
	double Length()const{
		return sqrt(x*x+y*y+z*z);
	}
	// ������λ��
	void Normalize(){ 
		double len = this->Length();
		x/=len;
		y/=len;
		z/=len;
	}			
	// ��������ͬ����ĵ�λ������
	CVector3 Normal()const{
		CVector3 v(*this);
		v.Normalize();
		return v;
	}	

public:
	// �������
	static CVector3 Add( const CVector3 &a, const CVector3 &b ){
		return CVector3( a.x+b.x, a.y+b.y, a.z+b.z );
	}
	// ��������
	static CVector3 Multiply( const CVector3 &a, const double &b ){
		return CVector3( a.x*b, a.y*b, a.z*b );
	}
	// �������нǵ�����ֵ
	static double CosOf( const CVector3 &a, const CVector3 &b ){
		return DotProduct(a,b) / a.Length() / b.Length();
	}		
	// �������ļнǣ��Ի��ȼ���
	static double AngleOf( const CVector3 &a, const CVector3 &b ){
		return acos(CosOf(a,b));
	}	
	// �������
	static double DotProduct( const CVector3 &a, const CVector3 &b ){
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}		
	// �������
	static CVector3 CrossProduct( const CVector3 &left, const CVector3 &right){
		return CVector3(left.y*right.z - left.z*right.y,
						left.z*right.x - left.x*right.z,
						left.x*right.y - left.y*right.x);
	}
	// a������b�ϵ�ͶӰ
	static CVector3 Project( const CVector3& a, const CVector3& b ){
		// �������b�ĳ��ȣ��õ�a��b�ϵ�ͶӰ���ȣ��ٳ���b�ķ�����������
		return DotProduct(a,b) / b.Length() * b.Normal();
	}
	// ��vͶӰ����normΪ���ߵ�ƽ����
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
	// ʵ�� ��ֵ�������� ������
	friend CVector3 operator*( const double b, const CVector3 &other ){
		return CVector3::Multiply(other,b);
	}
};
