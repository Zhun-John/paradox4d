#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"
#include "Maze4D.h"

extern class EMaze4D maze;

//��ά�Թ��е��������塣ÿ����������һ�����壬ÿ������ֻ�ܷ���һ�������У�һ��һ��ϵ��
class EItem4D
{
private:
    char* data;    //��ά�ռ���ÿ�����ӵ����壬'\0'����������
public:
	EItem4D(void):data(NULL){};
	~EItem4D(void){
		if (data!=NULL){
			free(data);
			data=NULL;
		}
    }
    
	//������ά����Ԫ��ֵ����α���Ϸ�
    char* ItemAt(int x,int y,int z,char d){
		return ItemAt( CIndex4(x,y,z,d) );
	}
	char* ItemAt(const CIndex4 &i){
		return data + i.OffsetInside(maze.size);
	}

public:
	//����ĳһ�ص���������λ������
	void LoadData(int level);

    // ���ܿ����������������ά�����Ӧλ�ã�д�������item
    void PlaceItem(char item, int x,int y,int z,char d){
		PlaceItem(item, CIndex4(x,y,z,d) );
	}
	void PlaceItem(char item, const CIndex4 &here){
		//����λ�ò��ڴ˲�
		if (*(maze.DataAt(here)) != here.d)
			return;

		//����λ���Ѿ������壬�Ҳ��ǿɲ��������壨����һ���ŵı�ǣ�
		char *itemHere = ItemAt(here);
		if ( *itemHere!='\0' && !(*itemHere>='0'&&*itemHere<='9') )
			return;//�򲻲��������壬ֱ�ӷ���

		//ÿ������ֻ�ܷ���һ�������У��Ƚ������ռ��еĴ�������գ�������·���
		CIndex4 i;
		i.Reset();
		do{
			itemHere = ItemAt(i);
			if (*itemHere==item)
				*itemHere = '\0';
		}while ( !i.IterateInside(maze.size) );

		//�������ܿ������������ά�������Ӧ��άλ���ϣ�д������������
		i.Reset(0,0,0,here.d);
		CIndex4 size = maze.size;
		size.d = here.d+1;
		do{
			//��d��ռ䣬���ϵ�ix,iy,izλ������dim��ռ�
			char dim = *(maze.DataAt(i));
			//dim��ռ俴��������λ��
			char see = *(maze.DataAt(here.x,here.y,here.z, dim));
			if (see == here.d)
				//��dim��ռ����Ӧλ�÷�������item
				*ItemAt(here.x,here.y,here.z, dim) = item;
		}while ( !i.IterateInside(size) );
	}

};
