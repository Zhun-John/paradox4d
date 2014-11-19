#pragma once
#include "global.h"

#define IMG_SUM 3			// ��������
#define LIST_SUM 3					// ��ʾ�б�����

class CglResouce
{
public:
    CglResouce();
    ~CglResouce();

    GLuint Lwall,Lceiling,Lground;		// ����ƽ�����ʾ�б�
    HFONT hFont;

public:
    void InitGL();
    void Init(int level);
    vector<int> Build3DText(unsigned char *str);

    //////////////////////////////////////////////////////////////////////////
private:
    GLuint texture[IMG_SUM];		// ����

    int LoadGLTextures(int level);
    void BuildWall();

    void CreateFont(char *facename, int height, int weight, bool italic,bool underline,bool strikeout);

};
