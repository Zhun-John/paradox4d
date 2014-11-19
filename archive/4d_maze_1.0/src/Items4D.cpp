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
    //����λ�ò��ڴ˲�
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
                    //���˸��ӷ����˴����壬�Ƚ�����ա�����÷ţ�֮�����̻����·���
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
                //�������ܿ������������ά�������Ӧ��άλ���ϣ�д������������
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
    memset(items,'\0',size);  //'\0'����������
}
