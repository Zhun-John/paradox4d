#pragma once

//��ά�Թ��е��������塣ÿ����������һ�����壬ÿ������ֻ�ܷ���һ�������У�һ��һ��ϵ��
class EItem4D
{
public:
    EItem4D(void);
    ~EItem4D(void);

    //��ʼ��ĳһ�ص���������λ������
    void Init(int level);

    //��Ⱦ����3D����
    void RenderAll3DItem();

    //���ݵ�ǰλ�ã�������Ļ������ʾ
    void Trigger2DRendering();

    //�ڵ�ǰλ�÷���һ������
    void PlaceItemHere(char item);

private:
//�ڱ�demo��������ά�ռ��У�ÿ�����Ӷ����ܱ�����ռ俴����������Ⱦʱ���뿼�����֡��ܿ������Ĺ�ϵ
//�����ֹ�ϵ������Maze4D���data�У�����ÿ�����壬�������ܿ����������в㣬������ʾ
    char* items;    //��ά�ռ���ÿ�����ӵ����壬'\0'����������

    //������ά����Ԫ��ֵ����α���Ϸ�
    char* ItemAt(int x,int y,int z,char d);

    // ���ܿ����������������ά�����Ӧλ��д������������item
    void PlaceItem(char item, int x,int y,int z,char d);

};
