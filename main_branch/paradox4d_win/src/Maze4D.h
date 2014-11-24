#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"

class EMaze4D
{
//�ڱ�demo��������ά�ռ��У�ÿ�����Ӷ����ܱ�����ռ俴����������Ⱦʱ���뿼�����֡��ܿ������Ĺ�ϵ
//�����ֹ�ϵ������Maze4D���data�У���
public:
	CIndex4 size;		// �Թ��ߴ磨��Ϊ�ַ�����xά���Ѷ���+1��
	CIndex4 start,end;	// �Թ������յ������
    char *data;         // ����Թ�����ά����m[d][z][y][x]�����һάx���ַ�������'\0'

public:
    EMaze4D(void):data(NULL){};
    ~EMaze4D(void){
		if (data!=NULL){
			free(data);
			data=NULL;
		}
	}
    //������ά����Ԫ��ֵ����ηǷ��򷵻�ǽ'.'��ָ��
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
    //����ĳһ�ص������Թ���������
    void LoadData(int level);

    //���ÿ�صĳ�ʼλ�ü�ά�ȡ�����Ϊtrue������㣬Ϊfalse�����յ�
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

    // �жϵ�ǰ�Ƿ�λ�������յ㣬1�����յ�(ȥ��һ��)��-1�������(ȥ��һ��)��0��������
    int LevelPortal(const CIndex4 &i){
		if (i==start)
			return -1;
		if (i==end)
			return 1;
		return 0;
	}

};

