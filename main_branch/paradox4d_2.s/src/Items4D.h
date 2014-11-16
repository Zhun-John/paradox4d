#pragma once
#include "global.h"
#include "Vector3.h"
#include "Index4.h"

#include "Maze4D.h"
#include "Tips.h"

extern class EMaze4D maze;
extern class ETips tips;

//��ά�Թ��е��������塣ÿ����������һ�����壬ÿ������ֻ�ܷ���һ�������У�һ��һ��ϵ��
class EItem4D
{
private:
    char* data;    //��ά�ռ���ÿ�����ӵ����壬'\0'����������
public:
	EItem4D(void):data(NULL){};
	~EItem4D(void){
		if (data!=NULL)
		{
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
    //��ʼ��ĳһ�ص���������λ������
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
/*	//ԭ�����ص���Ʒ
			PlaceItem('a',1,2,0,'A');
			PlaceItem('b',5,3,0,'I');
			PlaceItem('c',5,1,0,'F');
			PlaceItem('d',3,1,0,'H');
			PlaceItem('e',1,1,0,'H');*/
		}

	}

    //��Ⱦ����3D����
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
