#include "global.h"
#include "Items4D.h"
#include "Maze4D.h"
#include "Tips.h"

extern class EMaze4D maze;
extern class ETips tips;
extern int levelSum;

EItem4D::EItem4D(void)
    :items(NULL)
{
}

EItem4D::~EItem4D(void)
{
}

void EItem4D::PlaceItem( char item, int x,int y,int z,char d )
{
    //若此位置不在此层
    if (*(maze.Data(x,y,z,d)) != d)
    {
        return;
    }
    //若此位置已经有物体，且不是可擦除的物体（汉字一到九的标记），不擦除此物体，直接返回
    char *here = ItemAt(x,y,z,d);
    if ( *here!='\0' && !(*here>='0'&&*here<='9') )
    {
        return;
    }
    //每个物体只能放在一个方格中，先将整个空间中的此物体清空，随后重新放置
    for (int iz=0; iz<maze.mz; iz++)
    {
        for (int iy=0; iy<maze.my; iy++)
        {
            for (int ix = 0; ix < maze.mx; ix++)
            {
                for (char id='A'; id<maze.md; id++)
                {
                    char* here = ItemAt(ix,iy,iz,id);
                    if (*here==item)
                    {
                        *here = '\0';
                    }                
                }
            }
        }
    }
    //在所有能看到此物体的四维层里的相应三维位置上，写入此物体的索引
    for (int iz=0; iz<maze.mz; iz++)
    {
        for (int iy=0; iy<maze.my; iy++)
        {
            for (int ix = 0; ix < maze.mx; ix++)
            {
                char dim = *(maze.Data(ix,iy,iz,d));//对d层空间，其上的ix,iy,iz位置属于dim层空间
                char see = *(maze.Data(x,y,z,dim));//dim层空间看到的物体位置
                if (see == d)
                {
                    *ItemAt(x,y,z, dim) = item;//在dim层空间的相应位置放置物体item
                }
            }
        }
    }
}

char* EItem4D::ItemAt( int x,int y,int z,char d )
{
    return (items + x + (maze.mx+1) * ( y + maze.my * (z + maze.mz * (d-'A') ) ) );
}

void EItem4D::RenderAll3DItem()
{
    for( int iz=0; iz<maze.mz; iz++ )
        for( int iy=0; iy<maze.my; iy++ )
            for( int ix=0; ix<maze.mx; ix++ )
            {
                glPushMatrix();
                glTranslated( (ix+0.5), (iy+0.5), (iz+0.5) );
                glRotated(90,1,0,0);

                tips.Render3DTips( *ItemAt(ix,iy,iz,maze.currentDimension));

                glPopMatrix();
            }
}

void EItem4D::Trigger2DRendering()
{
    int ix,iy,iz;
    char id;
    maze.GetCurrentCoord(ix,iy,iz,id);
    char item = *ItemAt(ix,iy,iz,id);

    tips.Render2DTips(item);
}

void EItem4D::PlaceItemHere( char item )
{
    int ix,iy,iz;
    char id;
    maze.GetCurrentCoord(ix,iy,iz,id);
    PlaceItem(item,ix,iy,iz,id);
}
