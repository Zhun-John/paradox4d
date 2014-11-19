#pragma once
#include "global.h"

// 所有提示文字信息，某些作为3D字体摆在空间中，某些以2D字体打印在屏幕上
class ETips
{
// Tips类职责是保存文字信息，并根据物体索引item渲染2D/3D文字。它不关注这些物体被摆在何处
public:
    ETips(void);
    ~ETips(void);

    //初始化某一关的所有文字数据
	void Init(int level);

    //根据物体，在空间中渲染其对应的3D文字
    void Render3DTips(char item);

    //在屏幕上渲染2D的解说词
    void Render2DTips(char item);

private:
    //当前关卡所有3D字体的显示列表，每个vector<int>为一行字
    vector< vector<int> > list_font3D;

    //当前关卡所有解说字符串。若当前方格中有key物体，则在屏幕上显示value对应的多行文字
    map< char, vector<string> > font2D;
	
    //渲染一行3D文字，参数为其在list_font3D中的下标
    void Render3DString(int line);
};
