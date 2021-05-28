#ifndef __COLORS_H__
#define __COLORS_H__

#include <Windows.h>

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

#define SURFACE_COLOR		GRAY	
#define ON_SURFACE_COLOR	BLACK	

#define DIALOG_COLOR		WHITE	
#define ON_DIALOG_COLOR		BLACK	

#define PRIMARY_COLOR		VIOLET	
#define ACCENT_COLOR		RED		
#define SECONDARY_COLOR		YELLOW	

// 문자의 (foreground, background) 색상 설정
void textcolor(int foreground, int background);

#endif