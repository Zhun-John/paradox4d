#include "Tips.h"

void ETips::Init()
{
	BuildFont("����",40,40,0,0,0);

    font3D.clear();
// 3D��Ʒ ������ 0 ��ʼ
    font3D.push_back( Build3DText(" һ�����������߰˾�") );// 0123456789
    font3D.push_back( Build3DText("���") );// 
    font3D.push_back( Build3DText("�յ�") );// 
    font3D.push_back( Build3DText("��ʾ") );// Tips/Secrets~/����~
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
// 3D̨�� ������ 8 ��ʼ
    font3D.push_back( Build3DText("��ʱ��ᷢ��") );
    font3D.push_back( Build3DText("���ͻȻ����������") );
    font3D.push_back( Build3DText("����ԭ����������һ��") );
	font3D.push_back( Build3DText("��������ô���ط�") );
// 3D̨�� ������ 12 ��ʼ
	font3D.push_back( Build3DText("�ո�����") );
	font3D.push_back( Build3DText("Shift�½�") );
    

	
	fontHud.clear();
// Hud����Ӱ�����ƣ� ������ 0 ��ʼ
    fontHud.push_back( BuildHudText("�������ӽ�"));
    fontHud.push_back( BuildHudText("�Ա�ӽ�"));
    fontHud.push_back( BuildHudText("�����ӽ�"));
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud̨�ʣ��״νӴ�ÿ��3D����ʱ��̨�ʣ� ������ 7 ��ʼ����Ӧ��һ��
	fontHud.push_back( BuildHudText("���Ǹ�һ������һ�ߡ���") );
	fontHud.push_back( BuildHudText("���Ǹ�����������һ�ߡ���") );
	fontHud.push_back( BuildHudText("�õģ�һ�����������ˣ������ּ��ڷ�") );
	fontHud.push_back( BuildHudText("��ϲ��á��ġ�ͨ�˴") );
	fontHud.push_back( BuildHudText("��~ÿһ�ض���һ������") );

	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud���ؿ������� ������ 16 ��ʼ
    fontHud.push_back( BuildHudText("Level:1 �� ��"));
	fontHud.push_back( BuildHudText("Level:2 ��������"));
	fontHud.push_back( BuildHudText("Level:3 �� ��") );
    fontHud.push_back( BuildHudText("Level:4 �� ��"));
    fontHud.push_back( BuildHudText("Level:5 ƽ�潻��"));
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
// Hud̨�ʣ�ÿ������̨�ʣ� ������ 24 ��ʼ
    fontHud.push_back( BuildHudText("����WSAD��������"));
	fontHud.push_back( BuildHudText("���������ҵĸо�����") );
	fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText("�㲻�Ƿ��ݣ����������������� ָ����") );

    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
// Hud̨�ʣ�ÿ���յ��̨�ʣ� ������ 32 ��ʼ
	fontHud.push_back( BuildHudText("���س�,ȥ��һ��"));
	fontHud.push_back( BuildHudText("ÿ�ض���һ�����֣�ע���ռ���Ȼ�󡭡������Ҳ������·��") );
    fontHud.push_back( BuildHudText("׼����������һ����û��������") );
    fontHud.push_back( BuildHudText(" ") );

    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud̨�ʣ�һ�У� ������ 40 ��ʼ
	fontHud.push_back(BuildHudText("�ף����������ǲ�ͬ�Ŀռ䣿"));//a
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );//h
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );//m
// Hud̨�ʣ����У� ������ 53 ��ʼ
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );

}
