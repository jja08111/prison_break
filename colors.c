#include "colors.h"

// ������ (foreground, background) ���� ����
void textcolor(int foreground, int background)
{
	foreground &= 0xf;
	background &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (background << 4) | foreground);
}