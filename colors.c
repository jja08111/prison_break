#include "colors.h"

// 문자의 (foreground, background) 색상 설정
void textcolor(int foreground, int background)
{
	foreground &= 0xf;
	background &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}