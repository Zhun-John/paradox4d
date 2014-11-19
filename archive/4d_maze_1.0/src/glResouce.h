#pragma once
#include "global.h"

#define IMG_SUM 3			// 纹理总数
#define LIST_SUM 3					// 显示列表总数

class CglResouce
{
public:
    CglResouce();
    ~CglResouce();

    GLuint Lwall,Lceiling,Lground;		// 三种平面的显示列表
    HFONT hFont;

public:
    void InitGL();
    void Init(int level);
    vector<int> Build3DText(unsigned char *str);

    //////////////////////////////////////////////////////////////////////////
private:
    GLuint texture[IMG_SUM];		// 纹理

    int LoadGLTextures(int level);
    void BuildWall();

    void CreateFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout);

};
