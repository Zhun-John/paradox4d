#pragma once
#include "global.h"
#include "Maze4D.h"

//��ά�ռ��е�һ����ά����ͼ��
//ÿ������ֻ�ܷ�һ�����壬����Ҫ������壬��ʹ�ô���Ķ�����������Ⱦ
class EItems4D
{
public:
    EItems4D(void);
    virtual ~EItems4D(void);

    //���ܿ��������������λ��д������������item
    void PlaceItem(char item, int x,int y,int z,char d);

    void Init();
    void Render();
    
    char* ItemAt(int x,int y,int z,char d);

    virtual void RenderAt(int x,int y,int z,char d)=0;

private:
//�ڱ�demo��������ά�ռ��У�ÿ�����Ӷ����ܱ�����ռ俴����������Ⱦʱ���뿼�����֡��ܿ������Ĺ�ϵ
    //�����ֹ�ϵ������Maze4D���data�У�����ÿ�����壬�������ܿ����������в㣬������ʾ
    char* items; //������������ά�ռ��е�λ��

};

