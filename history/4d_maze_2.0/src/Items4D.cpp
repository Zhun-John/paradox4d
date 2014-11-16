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
    //����λ�ò��ڴ˲�
    if (*(maze.Data(x,y,z,d)) != d)
    {
        return;
    }
    //����λ���Ѿ������壬�Ҳ��ǿɲ��������壨����һ���ŵı�ǣ��������������壬ֱ�ӷ���
    char *here = ItemAt(x,y,z,d);
    if ( *here!='\0' && !(*here>='0'&&*here<='9') )
    {
        return;
    }
    //ÿ������ֻ�ܷ���һ�������У��Ƚ������ռ��еĴ�������գ�������·���
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
    //�������ܿ������������ά�������Ӧ��άλ���ϣ�д������������
    for (int iz=0; iz<maze.mz; iz++)
    {
        for (int iy=0; iy<maze.my; iy++)
        {
            for (int ix = 0; ix < maze.mx; ix++)
            {
                char dim = *(maze.Data(ix,iy,iz,d));//��d��ռ䣬���ϵ�ix,iy,izλ������dim��ռ�
                char see = *(maze.Data(x,y,z,dim));//dim��ռ俴��������λ��
                if (see == d)
                {
                    *ItemAt(x,y,z, dim) = item;//��dim��ռ����Ӧλ�÷�������item
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
