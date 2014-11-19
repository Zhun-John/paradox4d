#include "Tips.h"
#include "glResouce.h"

extern class CglResouce glRes;

ETips::ETips()
{
}

ETips::~ETips(void)
{
}

void ETips::Render3DString( int line )
{
    glPushMatrix();
    double scale = 1.0f/list_font3D[line].size();
    glScaled( scale, pow(scale,0.75), pow(scale,0.75) );
    glTranslated(-0.5*list_font3D[line].size(),0,0);

    for (unsigned i=0; i<list_font3D[line].size(); i++)
    {
        glCallList(list_font3D[line][i]);
    }
    glPopMatrix();
}

void ETips::Render3DTips( char item )
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
    glEnable(GL_TEXTURE_GEN_T);    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//GL_MODULATE);

    if( item>='1' && item<='9')
    {
        glPushMatrix();
        glScaled(0.7, 0.7, 0.7);
        glRotated((GetTickCount()/10)%360,0,1,0);
        glTranslated(-0.5,-0.5,0);
        glColor3d(0,0,1);
        glCallList(list_font3D[0][item-'0']);
        glPopMatrix();
    }
    if( item=='[' || item==']' )
    {
        glPushMatrix();
        glRotated((GetTickCount()/10)%360,0,1,0);
        glTranslated(0,-0.4,0);
        glColor3d(0,(item==']'),(item=='['));
        Render3DString(item=='['? 2:1);
        glPopMatrix();
    }
    if (item>='a' && item<='n')
    {
        glPushMatrix();
        glRotated((GetTickCount()/10)%360,0,1,0);
        glScaled(1.7,1.7,1.7);
        glTranslated(0.3,-0.2,0);
        glColor3d(1,0,0);
        Render3DString(3);
        glPopMatrix();
    }

//////////////////////////////////////////////////////////////////////////
    if ( item=='z' )
    {
        glPushMatrix();
        glRotated((GetTickCount()/30)%360,0,1,0);
        glTranslated(0,0.1,0);
        glColor3d(0,1,1);
        for (int i=4; i<=7; i++)
        {
            Render3DString(i);
            glTranslated(0,-0.2,0);
            glRotated(-30,0,1,0);
        }
        glPopMatrix();
    }

    glDisable(GL_TEXTURE_GEN_S);                // 使用自动生成纹理
    glDisable(GL_TEXTURE_GEN_T);   
    glColor3d(1,1,1);
}

void ETips::Render2DTips( char item )
{
    glLoadIdentity();
    //永久显示关卡信息
    for (unsigned i=0; i<font2D.at('=').size(); i++)
    {
        glRasterPos2f(-0.9+0.6*i,-0.9);
        glRes.drawCNString(font2D.at('=').at(i).c_str());
    }

    //查找此物体是否触发解说词
    if (font2D.find(item)!=font2D.end())
    {
        for (unsigned i=0, n=font2D.at(item).size(); i<n; i++)
        {
            glRasterPos2f(-0.9,-0.8+0.15*(n-i));
            glRes.drawCNString(font2D.at(item).at(i).c_str());
        }
    }
}
