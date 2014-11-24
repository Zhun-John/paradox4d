#include "Items4D.h"

void EItem4D::LoadData(int level){
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
		PlaceItem('Y',3,4,0,'A');
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
