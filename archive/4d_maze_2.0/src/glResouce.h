#pragma once
#include "global.h"

#define IMG_SUM 4			// 纹理总数

class CglResouce
{
public:
    CglResouce();
    ~CglResouce();

    GLuint LwallX,LwallY,Lceiling,Lground;		// 四种平面的显示列表
    HFONT hFont;

public:
    int LoadGLTextures(int level);
    void BuildWall();
    vector<int> Build3DText(unsigned char *str);
    void drawCNString(const char* str);
    void BuildFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout);

    //void selectFont(int size, int charset, const char* face);
    //void Init(int level);
private:
    GLuint texture[IMG_SUM];		// 纹理

};
