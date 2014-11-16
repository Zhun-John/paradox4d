#pragma once

#include <gl/glut.h>
#include <gl/glaux.h>
#include <stdio.h>
#include <stdlib.h>		
#include <math.h>
#include <windows.h>
#include <winuser.h>
#include <assert.h>
#include <vector>
#include <map>
using namespace std;


#define M_PI       3.14159265358979323846
#define ZERO(d)    ( abs(d)<0.000001f )
#define SIGNOF(d)  ( (d)/abs(d) )       // 返回1或-1代表此数值的正负
