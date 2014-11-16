#include "Info.h"
#include "glResouce.h"

extern class CglResouce glRes;
extern class EMaze4D maze;

EInfo::EInfo()
{
}

EInfo::~EInfo(void)
{
}

void EInfo::Init(int level)
{
    EItems4D::Init();
    infoText.clear();

    infoText.push_back( glRes.Build3DText((unsigned char*)" һ�����������߰˾�") );

    //a 1-2
    infoText.push_back( glRes.Build3DText((unsigned char*)"WELCOME!") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"һ�����������Թ�") );
    //b
    infoText.push_back( glRes.Build3DText((unsigned char*)"һ����ʵ������") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"�����ܴ��ڵ��Թ�") );
    //c 5
    infoText.push_back( glRes.Build3DText((unsigned char*)"���Ҽ�ƽ��") );
    //d
    infoText.push_back( glRes.Build3DText((unsigned char*)"�ڽ���ƽ��") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"�㽫�����Ǹ�����") );
    //e 8-11
    infoText.push_back( glRes.Build3DText((unsigned char*)"��ʱ��ᷢ��") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"���ͻȻ����������") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"����ԭ����������һ��") );
    infoText.push_back( glRes.Build3DText((unsigned char*)"��������ô���ط�") );
    //b
//     infoText.push_back( glRes.Build3DText((unsigned char*)"������ʵ��������Զ�޷����") );

    PlaceItem('a',3,2,0,'A');
    PlaceItem('b',1,2,0,'A');
    PlaceItem('c',0,3,0,'A');
    PlaceItem('d',0,1,0,'A');
    PlaceItem('e',2,3,0,'T');
}

void EInfo::RenderAt( int x,int y,int z,char d )
{
//    glRotated((GetTickCount()/10)%360,0,1,0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
    glEnable(GL_TEXTURE_GEN_T);    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//GL_MODULATE);

    char item = *ItemAt(x,y,z,d);
    if( item>='1' && item<='9')
    {
        glPushMatrix();
        glScaled(0.7, 0.7, 0.7);
        glRotated((GetTickCount()/10)%360,0,1,0);
        glTranslated(-0.5,-0.3,0);
        glColor3d(0,0,1);
        glCallList(infoText[0][item-'0']);
        glPopMatrix();
    }
    if ( item=='a' )
    {
        glPushMatrix();
        glScaled(0.2, 0.2, 0.2);
        glTranslated(1.5,0,0);
        glColor3d(0,1,0);
        DrawLine(1);

        glTranslated(-2.5,-1,0);
        glScaled(0.8, 0.8, 0.8);
        glColor3d(1,0,0);
        DrawLine(2);
        glPopMatrix();
    }
    if ( item=='b' || item=='d' )
    {
        glPushMatrix();
        glScaled(0.2, 0.2, 0.2);
        glTranslated(0,-1,0);
        glRotated(item=='d'?135:45,0,1,0);
        glColor3d(0,1,0);
        DrawLine(item=='b'?3:6);

        glTranslated(-0.3,-1,0);
        glScaled(0.8, 0.8, 0.8);
        glColor3d(1,0,0);
        DrawLine(item=='b'?4:7);
        glPopMatrix();
    }
    if ( item=='c' )
    {
        glPushMatrix();
        glScaled(0.2, 0.2, 0.2);
        glTranslated(-0.3,-2,0);
        glColor3d(0,1,0);
        DrawLine(5);
        glPopMatrix();
    }
    if ( item=='e' )
    {
        glPushMatrix();
        glRotated((GetTickCount()/30)%360,0,1,0);
        glScaled(0.2, 0.2, 0.2);
        glTranslated(0,1.5,0);
        glColor3d(0,1,1);
        for (int i=8; i<12; i++)
        {
            DrawLine(i);
            glTranslated(0,-1,0);
            glRotated(-30,0,1,0);
        }
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_GEN_S);                // ʹ���Զ���������
    glDisable(GL_TEXTURE_GEN_T);   
    glColor3d(1,1,1);
}

void EInfo::DrawLine( int line )
{
    glPushMatrix();
    glTranslated(-0.9*(infoText[line].size())/2,0,0);

    for (unsigned i=0; i<infoText[line].size(); i++)
    {
        glCallList(infoText[line][i]);
    }
    glPopMatrix();
}
