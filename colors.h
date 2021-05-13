#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

#define BLACK		0  

#define RED2		12 
#define MAGENTA2	13 
#define YELLOW2		14 

#define WHITE2      7
#define WHITE1		15 

#define BACKGROUND_COLOR	WHITE1
#define ON_BACKGROUND_COLOR BLACK

#define SURFACE_COLOR		WHITE2
#define ON_SURFACE_COLOR	BLACK

#define PRIMARY_COLOR		MAGENTA2
#define SECONDARY_COLOR		YELLOW2

// 문자의 (foreground, background) 색상 설정
void _textcolor(int color, int bgcolor);

void setPlayerIconColor();
void setWallIconColor();
void setEmptyIconColor();

#endif