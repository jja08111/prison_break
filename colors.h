#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

#define HEX_DEFAULT_COLOR	0x00aabbcc

#define BLACK		0  

#define RED2		12 
#define MAGENTA2	13 
#define YELLOW2		14 
#define GREEN		2
#define DARK_GRAY   8

#define GREY      7
#define WHITE1		15 

#define BACKGROUND_COLOR	WHITE1	// 하양
#define ON_BACKGROUND_COLOR BLACK	// 검정

#define SURFACE_COLOR		GREY	// 회색
#define ON_SURFACE_COLOR	BLACK	// 검정

#define DIALOG_COLOR		WHITE1	// 하양
#define ON_DIALOG_COLOR		BLACK	// 검정

#define PRIMARY_COLOR		MAGENTA2// 보라
#define SECONDARY_COLOR		YELLOW2 // 노랑
#define ACCENT_COLOR		RED2	// 빨강

#define MOB_VISION_COLOR	YELLOW2	// 노랑

// 문자의 (foreground, background) 색상 설정
void textcolor(int color, int bgcolor);

#endif