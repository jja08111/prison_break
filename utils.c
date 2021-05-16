#include "utils.h"

void removeCursor(void) { 

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void goto2xy(int x, int y)
{
	COORD pos = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void gotoPosition(COORD position)
{
	goto2xy(position.X, position.Y);
}

void gotoCenterForAlignString(SMALL_RECT rect, const char* str)
{
	int x = (rect.Left + rect.Right) / 2 - (strlen(str) / 2);

	gotoPosition((COORD) { x, rect.Top });
}

int samePosition(COORD a, COORD b)
{
	if (a.X == b.X && a.Y == b.Y)
		return 1;
	return 0;
}