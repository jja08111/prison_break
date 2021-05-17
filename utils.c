#include "utils.h"

static void _gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void removeCursor(void) { 

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void goto2xy(int x, int y)
{
	_gotoxy(2 * x, y);
}

void gotoPosition(COORD position)
{
	goto2xy(position.X, position.Y);
}

void gotoCenterForAlignString(
	SMALL_RECT	rect,
	const char* str
)
{
	int x = (rect.Left + rect.Right) - (strlen(str) / 2);
	int y = (rect.Top + rect.Bottom) / 2;

	_gotoxy(x, y);
}

int samePosition(COORD a, COORD b)
{
	if (a.X == b.X && a.Y == b.Y)
		return 1;
	return 0;
}

int rangedNum(int num, int minNum, int maxNum)
{
	return max(minNum, min(num, maxNum));
}

Direction getDirectionFrom(COORD start, COORD end)
{
	if (start.Y > end.Y)
		return DIRECTION_UP;
	else if (start.Y < end.Y)
		return DIRECTION_DOWN;
	else if (start.X > end.X)
		return DIRECTION_LEFT;
	else if (start.X < end.X)
		return DIRECTION_RIGHT;
	return DIRECTION_UP;
}

int inRangeRect(COORD point, SMALL_RECT range)
{
	return (range.Left <= point.X && point.X <= range.Right)
		&& (range.Top <= point.Y && point.Y <= range.Bottom);
}