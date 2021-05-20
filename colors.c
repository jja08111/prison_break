#include "colors.h"

// 문자의 (foreground, background) 색상 설정
void textcolor(int fgColor, int bgColor)
{
	fgColor &= 0xf;
	bgColor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | fgColor);
}