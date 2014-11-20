#include "Tips.h"

void ETips::Init()
{
	BuildFont("黑体",40,40,0,0,0);

    font3D.clear();
// 3D物品 索引从 0 开始
    font3D.push_back( Build3DText(" 一二三四五六七八九") );// 0123456789
    font3D.push_back( Build3DText("起点") );// 
    font3D.push_back( Build3DText("终点") );// 
    font3D.push_back( Build3DText("提示") );// Tips/Secrets~/秘密~
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
    font3D.push_back( Build3DText(" ") );
// 3D台词 索引从 8 开始
    font3D.push_back( Build3DText("有时你会发现") );
    font3D.push_back( Build3DText("你会突然跳出这世界") );
    font3D.push_back( Build3DText("发现原来，曾经的一切") );
	font3D.push_back( Build3DText("不过就这么大点地方") );
// 3D台词 索引从 12 开始
	font3D.push_back( Build3DText("空格上升") );
	font3D.push_back( Build3DText("Shift下降") );
    

	
	fontHud.clear();
// Hud（摄影机名称） 索引从 0 开始
    fontHud.push_back( BuildHudText("地球人视角"));
    fontHud.push_back( BuildHudText("宇航员视角"));
    fontHud.push_back( BuildHudText("智能视角"));
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud台词（首次接触每个3D物体时的台词） 索引从 7 开始，对应“一”
	fontHud.push_back( BuildHudText("这是个一，但另一边……") );
	fontHud.push_back( BuildHudText("这是个二货，但另一边……") );
	fontHud.push_back( BuildHudText("好的，一二三都归你了，按数字键摆放") );
	fontHud.push_back( BuildHudText("恭喜获得“四”通八达！") );
	fontHud.push_back( BuildHudText("五~每一关都有一个物体") );

	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud（关卡描述） 索引从 16 开始
    fontHud.push_back( BuildHudText("Level:1 立 柱"));
	fontHud.push_back( BuildHudText("Level:2 田字迷乱"));
	fontHud.push_back( BuildHudText("Level:3 层 叠") );
    fontHud.push_back( BuildHudText("Level:4 自 由"));
    fontHud.push_back( BuildHudText("Level:5 平面交错"));
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
// Hud台词（每关起点的台词） 索引从 24 开始
    fontHud.push_back( BuildHudText("键盘WSAD……走起！"));
	fontHud.push_back( BuildHudText("来享受迷乱的感觉……") );
	fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText("你不是风筝！不再有绳索束缚你 指引你") );

    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
// Hud台词（每关终点的台词） 索引从 32 开始
	fontHud.push_back( BuildHudText("按回车,去下一关"));
	fontHud.push_back( BuildHudText("每关都有一个数字，注意收集，然后……你就再也不怕迷路了") );
    fontHud.push_back( BuildHudText("准备好了吗？下一关是没有重力的") );
    fontHud.push_back( BuildHudText(" ") );

    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
    fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
// Hud台词（一行） 索引从 40 开始
	fontHud.push_back(BuildHudText("咦？左右两侧是不同的空间？"));//a
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
// Hud台词（两行） 索引从 53 开始
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );
	fontHud.push_back( BuildHudText(" ") );

}
