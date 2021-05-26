#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

//색상
typedef enum _Colors {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VIOLET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
} Colors;

#define BACKGROUND_COLOR	BLACK	
#define ON_BACKGROUND_COLOR WHITE	

#define SURFACE_COLOR		GRAY	// 회색
#define ON_SURFACE_COLOR	BLACK	// 검정

#define DIALOG_COLOR		WHITE	// 하양
#define ON_DIALOG_COLOR		BLACK	// 검정

#define PRIMARY_COLOR		VIOLET	// 보라
#define ACCENT_COLOR		RED		// 빨강
#define SECONDARY_COLOR		YELLOW	// 노랑

// 문자의 (foreground, background) 색상 설정
void textcolor(int color, int bgcolor);

#endif