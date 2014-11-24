#pragma once

#include <stdio.h>
#include <stdlib.h>	
#include "freeglut.h"
#include "glaux.h"
#include <math.h>
#include <windows.h>
#include <winuser.h>
#include "wingdi.h"
#include <assert.h>
#include <vector>
using namespace std;

#define M_PI			3.1415926535897932384
#define IS_ZERO(d)    ( abs((double)d)<0.000001f )
// 返回1或-1代表此数值的正负
#define SIGNOF(d)  ( IS_ZERO(d) ? 1 : (d)/abs((double)d) )
