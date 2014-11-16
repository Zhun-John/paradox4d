#include "global.h"
#include "Items4D.h"
#include "Maze4D.h"

extern class EMaze4D maze;

// EItem4D::Init 中存储了所有物体的位置信息
void EItem4D::Init(int level)
{
    if (items) free(items);
    int size = (maze.mx+1)*maze.my*maze.mz*(maze.md-'A');
    items = (char*)malloc( size );
    if (!items) exit(0);

    memset(items,'\0',size);
    PlaceItem('[',maze.sx,maze.sy,maze.sz,maze.sd);
    PlaceItem(']',maze.ex,maze.ey,maze.ez,maze.ed);

    if (level==1)
    {
        PlaceItem('a',5,4,0,'A');
    }

    if (level==2)
    {
        PlaceItem('a',2,2,4,'A');
        PlaceItem('b',2,2,6,'A');
        PlaceItem('c',2,2,7,'A');
        PlaceItem('d',0,0,7,'A');
    }

    if (level==3)
    {
        PlaceItem('b',3,2,2,'A');
        PlaceItem('c',0,2,0,'A');
        PlaceItem('d',4,4,4,'A');
    }

    if (level==4)
    {
        PlaceItem('a',4,5,3,'A');
        PlaceItem('b',2,1,5,'A');
    }

    if (level==5)
    {
        PlaceItem('a',1,2,0,'A');
        PlaceItem('b',5,3,0,'I');
        PlaceItem('c',5,1,0,'F');
        PlaceItem('d',3,1,0,'H');
        PlaceItem('e',1,1,0,'H');
    }

    if (level==6)
    {
        PlaceItem('z',2,3,0,'T');
    }
}
