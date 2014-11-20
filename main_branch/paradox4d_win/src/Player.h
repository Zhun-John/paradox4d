#pragma once
#include "Maze4D.h"

extern class EMaze4D maze;

class CPlayer
{
public:
    char dim;  //��ҵ�ǰ������ά��
    const double manSize;   //��ҵĳߴ磬����ǽ�����С����
public:
	CPlayer(void):dim(INDEX4_BASE),manSize(0.2f){};
	~CPlayer(void){};

public:
    //��õ�ǰά���£�ĳλ�ö�Ӧ���Թ���������
    CIndex4 GetCurrentIndex(const CVector3 &pos){
		CIndex4 i = CIndex4::FromPosition(pos.x,pos.y,pos.z);
		i.d = dim;
		i.d = *maze.DataAt(i);
		return i;
	}

	void Move(CVector3 &pos, CVector3 &delta){
		// ÿ���ƶ����벻�ܳ���mansize/2
		if (delta.Length() > manSize/2){
			delta.Normalize();
			delta *= manSize/2;
		}

		// �ƶ�
		pos += delta;

		// ���⴩ǽ
		CollisionDefend(pos);

		// ��D�����Ĳ���
		CIndex4 i = GetCurrentIndex(pos);
		dim = *(maze.DataAt(i) );
	}

private:
    //���⴩ǽ
    void CollisionDefend(CVector3 &pos){
		CIndex4 i = CIndex4::FromPosition(pos.x,pos.y,pos.z);
		i.d = dim;

		//��ǰλ���뷽�����ĵľ���
		double disX = (pos.x - i.x) - 0.5;
		double disY = (pos.y - i.y) - 0.5;
		double disZ = (pos.z - i.z) - 0.5;

		//��������ײʱ����ά���뷽�����ĵ�������
		double maxDis = 0.5-manSize;   

		// ��X�����Ͻӽ������Ե���鿴X�������Ƿ���ǽ���ڡ�YZͬ��
		if ( abs(disX) > maxDis )
			if ( *maze.DataAt((disX>0?i.x+1:i.x-1),i.y,i.z,i.d)=='.' )
				disX = disX>0? maxDis : -maxDis;

		if ( abs(disY) > maxDis )
			if ( *maze.DataAt(i.x,(disY>0?i.y+1:i.y-1),i.z,i.d)=='.' )
				disY = disY>0? maxDis : -maxDis;

		if ( abs(disZ) > maxDis )
			if ( *maze.DataAt(i.x,i.y,(disZ>0?i.z+1:i.z-1),i.d)=='.' )
				disZ = disZ>0? maxDis : -maxDis;

		// ���ӽ���һ����ֱ���⣬���ж϶ԽǷ����Ƿ�Ϊǽ��YZ/ZXͬ��
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

		//���ӽ�һ����
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

