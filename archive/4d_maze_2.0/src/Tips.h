#pragma once
#include "global.h"

// ������ʾ������Ϣ��ĳЩ��Ϊ3D������ڿռ��У�ĳЩ��2D�����ӡ����Ļ��
class ETips
{
// Tips��ְ���Ǳ���������Ϣ����������������item��Ⱦ2D/3D���֡�������ע��Щ���屻���ںδ�
public:
    ETips(void);
    ~ETips(void);

    //��ʼ��ĳһ�ص�������������
	void Init(int level);

    //�������壬�ڿռ�����Ⱦ���Ӧ��3D����
    void Render3DTips(char item);

    //����Ļ����Ⱦ2D�Ľ�˵��
    void Render2DTips(char item);

private:
    //��ǰ�ؿ�����3D�������ʾ�б�ÿ��vector<int>Ϊһ����
    vector< vector<int> > list_font3D;

    //��ǰ�ؿ����н�˵�ַ���������ǰ��������key���壬������Ļ����ʾvalue��Ӧ�Ķ�������
    map< char, vector<string> > font2D;
	
    //��Ⱦһ��3D���֣�����Ϊ����list_font3D�е��±�
    void Render3DString(int line);
};
