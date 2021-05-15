#include "colors.h"

// 문자의 (foreground, background) 색상 설정
static void _textcolor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void setPlayerIconColor()
{
	_textcolor(PRIMARY_COLOR, SURFACE_COLOR);
}

void setWallIconColor()
{
	_textcolor(ON_SURFACE_COLOR, SURFACE_COLOR);
}

void setEmptyIconColor()
{
	_textcolor(ON_SURFACE_COLOR, SURFACE_COLOR);
}