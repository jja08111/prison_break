#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

#define BLACK		0  

#define RED			12 
#define MAGENTA		13 
#define YELLOW		14 
#define GREEN		2
#define DARK_GRAY   8

#define GRAY		7
#define WHITE		15 

#define BACKGROUND_COLOR	WHITE	// 하양
#define ON_BACKGROUND_COLOR BLACK	// 검정

#define SURFACE_COLOR		GRAY	// 회색
#define ON_SURFACE_COLOR	BLACK	// 검정

#define DIALOG_COLOR		WHITE	// 하양
#define ON_DIALOG_COLOR		BLACK	// 검정

#define PRIMARY_COLOR		MAGENTA	// 보라
#define SECONDARY_COLOR		YELLOW	// 노랑
#define ACCENT_COLOR		RED		// 빨강

#define MOB_VISION_COLOR	YELLOW	// 노랑

// 문자의 (foreground, background) 색상 설정
void textcolor(int color, int bgcolor);

#endif