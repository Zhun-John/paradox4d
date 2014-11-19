#include "Items4D.h"

extern class EMaze4D maze;

EItems4D::EItems4D(void)
{
}

EItems4D::~EItems4D(void)
{
}

void EItems4D::PlaceItem( char item, int x,int y,int z,char d )
{
    //若此位置不在此层
    if (*(maze.Data(x,y,z,d)) != d)
    {
        return;
    }
    for (int iz=0; iz<maze.mz; iz++)
    {
        for (int iy=0; iy<maze.my; iy++)
        {
            for (int ix = 0; ix < maze.mx; ix++)
            {
                for (char id='A'; id<maze.md; id++)
                {
                    //若此格子放置了此物体，先将其清空。如果该放，之后立刻会重新放置
                    if (*ItemAt(ix,iy,iz,id)==item)
                    {
                        *ItemAt(ix,iy,iz,id) = '\0';
                    }
                
                }
            }
        }
    }
    for (int iz=0; iz<maze.mz; iz++)
    {
        for (int iy=0; iy<maze.my; iy++)
        {
            for (int ix = 0; ix < maze.mx; ix++)
            {
                //在所有能看到此物体的四维层里的相应三维位置上，写入此物体的索引
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

char* EItems4D::ItemAt( int x,int y,int z,char d )
{
    return (items + x + (maze.mx+1) * ( y + maze.my * (z + maze.mz * (d-'A') ) ) );
}

void EItems4D::Render()
{
    for( int iz=0; iz<maze.mz; iz++ )
        for( int iy=0; iy<maze.my; iy++ )
            for( int ix=0; ix<maze.mx; ix++ )
            {
                glPushMatrix();
                glTranslated( (ix+0.5), (iy+0.5), (iz+0.5) );
                glRotated(90,1,0,0);

                RenderAt(ix,iy,iz,maze.currentDimension);

                glPopMatrix();
            }
}

void EItems4D::Init()
{
    int size = (maze.mx+1)*maze.my*maze.mz*(maze.md-'A');
    items = (char*)malloc( size );
    memset(items,'\0',size);  //'\0'代表无物体
}
