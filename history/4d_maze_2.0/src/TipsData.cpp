#include "Tips.h"
#include "glResouce.h"

extern class CglResouce glRes;

//�洢�����������ݣ�������˵�ʺ�3D����
void ETips::Init(int level)
{
    static bool isFirstCall=true;
    if (isFirstCall)    // �״ε��ã�����ͨ����Ϣ
    {
        isFirstCall = false;

        // list_font3D����0-3Ϊͨ��
        list_font3D.clear();
        list_font3D.push_back( glRes.Build3DText((unsigned char*)" Ҽ�����������߰˾�") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"�յ�") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"���") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"Tips") );
    }
    else        // ���״ε��ã������һ�ص���Դ
    {
        while (list_font3D.size() >4 )
        {
            vector<int>::iterator i = list_font3D.back().begin();
            while (i!=list_font3D.back().end())
            {
                glDeleteLists(*i, 1); // ɾ����ʾ�б�
                ++i;
            }
            list_font3D.pop_back();
        }
    }
//////////////////////////////////////////////////////////////////////////
    std::pair<char,vector<string>> temp;
    font2D.clear();

    if (level==1)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��1�أ�ƽ̹");
        temp.second.push_back("�Թ�ά�ȣ�XY");
        temp.second.push_back("��Ӱ�����ͣ�plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("�㽫�����������ɵ�3D�ռ䣬");
        temp.second.push_back("�Լ����������4D�ռ䡣");
        temp.second.push_back("����֮ǰ�������ȸ�ϰһ��2D��ƽ��");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("����Ҽ���ƽ�ơ�����");
        temp.second.push_back("���˫��ͬ��������");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("����XY��������ף����ǲ������ǵ�Ŀ��");
        temp.second.push_back("����Ҫ���������ά��");
        temp.second.push_back("��Enterȥ��һ��");
        font2D.insert(temp);
    }

    if (level==2)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��2�أ����");
        temp.second.push_back("�Թ�ά�ȣ�XYz");
        temp.second.push_back("��Ӱ�����ͣ�plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("���ǳ�������3D�ռ䣬�൱��һ����¥�Ķ��¥��");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("�з�о�������3D�����Ƕ��2D�ļ򵥵��ӣ�");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("2D������һ�����3D��");
        temp.second.push_back("������Z������������Z����Ժ�XY�����⻥����");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("���ܡ���Ϊ����ʼ����վ���ŵģ�ͷ����Զ���ϡ�");
        temp.second.push_back("��������Ӱ�죬����ϰ�����������ơ�");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("�������������ǵ�ͷ���������������ǵ�˼ά��ʽ��");
        temp.second.push_back("��ʹ������������ά���������ƶ���������Ȼ��2D��");
        temp.second.push_back("��̬�����仮��Ϊ����ȸ��棬�ص���һ�������3D");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("�����Թ����ᷭת����Z����XY���ܻ��������z��Сд");
        temp.second.push_back("��һ�أ����ǽ����������ͷ����");
        font2D.insert(temp);
    }

    if (level==3)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��3�أ��ܵ��ݺ�");
        temp.second.push_back("�Թ�ά�ȣ�XYZ");
        temp.second.push_back("��Ӱ�����ͣ�free3D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("�㲻�Ƿ��ݡ����������������㡡ָ����");
        temp.second.push_back("ȥ�ɣ�");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("û��������������Լ���������");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("����˳ʱ���ƶ���꣬��׼��������Ȧ");
        temp.second.push_back("���С�����ܰ��������ת����");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("�����һֱ���ƣ�����շ�");
        temp.second.push_back("����������ⷽ�����޷�ת");
        temp.second.push_back("���ɵ�3D��Ӱ��");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("��Ӱ�������ǵ��۾���");
        temp.second.push_back("�Ϸ����������ͷ���ķ���");
        temp.second.push_back("��һ�أ�����ʹ����һ�ָ����ܵ�3D��Ӱ��");
        font2D.insert(temp);
    }

    if (level==4)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��4�أ�ƽ�潻��");
        temp.second.push_back("�Թ�ά�ȣ�XYZ");
        temp.second.push_back("��Ӱ�����ͣ�auto3D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("�Թ�λ��Ӱ�������Ϸ�����Զ�ƥ�������������");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("վ�ڷ������룬������ֱ���⣬����̧ͷ���ͷ");
        temp.second.push_back("�������Թ�λ����");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("��Ӧ�÷����ˣ�X�����ǽ����һ���ģ�Y����Ҳ��");
        temp.second.push_back("��Z����컨��͵ذ岻ͬ�����ܰ���ȷ�Ϸ���");
        temp.second.push_back("�������е�������ǿ������ҷ�������ѩn��b��");
        temp.second.push_back("��Ϊ������̽���� ����ʿ ������");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("��һ�أ����ǽ�̽�����Թ�����4D�Ŀ�����");
        font2D.insert(temp);
    }

    if (level==5)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��5�أ�����");
        temp.second.push_back("�Թ�ά�ȣ�XYw");
        temp.second.push_back("��Ӱ�����ͣ�plain2D");
        font2D.insert(temp);

        temp.first = '[';
        temp.second.clear();
        temp.second.push_back("�������ڶ�ά�Ļ����ϣ��ѵ��ĸ�ά��ͶӰ����");
        font2D.insert(temp);

        temp.first = 'a';
        temp.second.clear();
        temp.second.push_back("���������������������ǲ�ͬ�Ŀռ������߿�");
        font2D.insert(temp);

        temp.first = 'b';
        temp.second.clear();
        temp.second.push_back("����������ת�Ĺ����У����ĸ�ά��W�ϵġ��߶ȡ��������ӣ�");
        temp.second.push_back("��һȦ��ʹW��������1����������һ��ƽ�е���ά�ռ�");
        font2D.insert(temp);

        temp.first = 'c';
        temp.second.clear();
        temp.second.push_back("��������������¥���ߣ���������ֱ�ĸ߶ȣ�");
        temp.second.push_back("�����¥����һ��һ�������������תʹ����");
        temp.second.push_back("�����˵���ά�ϵĸ߶ȣ�������һ����ά�ռ�");
        font2D.insert(temp);

        temp.first = 'd';
        temp.second.clear();
        temp.second.push_back("����XYz�͵Ŀռ�����ƣ��Ѹ�ά�ֳ��˺ܶ��");
        temp.second.push_back("��ά�Ĳ㣬Ȼ���ص���Щ�㣬�������ά�ռ䡣");
        temp.second.push_back("���wҲ��Сд");
        font2D.insert(temp);

        temp.first = 'e';
        temp.second.clear();
        temp.second.push_back("������Ƭ�ռ��������ģ�����ʵ����һ���������ڸ��ѡ�");
        temp.second.push_back("�������԰�����1-9��0Ϊ���������ǿ��԰��������Ƭ�ռ䡣");
        font2D.insert(temp);

        temp.first = ']';
        temp.second.clear();
        temp.second.push_back("����4D�����ϸ񣬽���Ϊһ�ֱ�﷽ʽ���ɲο�ά���ٿ�");
        temp.second.push_back("���ˣ�5����ѧ�ؿ�������");
        temp.second.push_back("δ������Ŀ�Դ�����");
        font2D.insert(temp);

    }

    if (level==6)
    {
        temp.first = '=';
        temp.second.clear();
        temp.second.push_back("��6�أ���������");
        temp.second.push_back("�Թ�ά�ȣ�XYw");
        temp.second.push_back("��Ӱ�����ͣ�plain2D");
        font2D.insert(temp);
        
        // 3D��������4-7
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"��ʱ��ᷢ��") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"���ͻȻ����������") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"����ԭ����������һ��") );
        list_font3D.push_back( glRes.Build3DText((unsigned char*)"��������ô���ط�") );
    }

//////////////////////////////////////////////////////////////////////////
}
