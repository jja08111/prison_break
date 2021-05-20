#include "colors.h"

// ������ (foreground, background) ���� ����
void textcolor(int fgColor, int bgColor)
{
	fgColor &= 0xf;
	bgColor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | fgColor);
}