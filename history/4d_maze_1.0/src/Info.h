#pragma once
#include "global.h"
#include "Items4D.h"

// �ڿռ��л��Ƶ�����������Ϣ
class EInfo
    : public EItems4D
{
public:
    EInfo(void);
    virtual ~EInfo(void);

	void Init(int level);

private:
    vector< vector<int> > infoText;
	
    void RenderAt(int x,int y,int z,char d);
    void DrawLine(int line);
};

