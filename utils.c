#include "utils.h"

void gotoxy(int x, int y)
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
	gotoxy(2 * x, y);
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

	gotoxy(x, y);
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

Direction getDirectionFrom(COORD before, COORD after)
{
	if (before.Y > after.Y)
		return DIRECTION_UP;
	else if (before.Y < after.Y)
		return DIRECTION_DOWN;
	else if (before.X > after.X)
		return DIRECTION_LEFT;
	else if (before.X < after.X)
		return DIRECTION_RIGHT;
	return DIRECTION_UP;
}

int inRangeRect(COORD point, SMALL_RECT range)
{
	return (range.Left <= point.X && point.X <= range.Right)
		&& (range.Top <= point.Y && point.Y <= range.Bottom);
}

Direction turnRightDirection(Direction direction)
{
	direction++;
	return direction % 4;
}

Direction turnLeftDirection(Direction direction)
{
	direction += 3;
	return direction % 4;
}

Direction reverseDirection(Direction direction)
{
	direction += 2;
	return direction % 4;
}

COORD getMovedCoordInDirection(COORD coord, Direction direction)
{
	switch (direction)
	{
	case DIRECTION_LEFT:
		coord.X--;
		break;
	case DIRECTION_UP:
		coord.Y--;
		break;
	case DIRECTION_RIGHT:
		coord.X++;
		break;
	case DIRECTION_DOWN:
		coord.Y++;
	}
	return coord;
}