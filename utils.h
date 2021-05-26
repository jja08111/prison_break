#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>
#include <stdlib.h> // min, max
#include <math.h>

typedef enum _Direction {
	DIRECTION_LEFT,
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN
} Direction;

void gotoxy(int x, int y);

void removeCursor(void);

// Ŀ���� (2x, y) ��ǥ�� �̵���Ų��.
void goto2xy(int x, int y);

// Ŀ���� (2 * position.X, position.Y) ��ǥ�� �̵���Ų��.
void gotoPosition(COORD position);

// x ���� 2ĭ�� �� ĭ���� �ξ� ����Ѵ�.
void gotoCenterForAlignString(
	SMALL_RECT	rect, 
	const char* str
);

// ������ 1, �ٸ��� 0�� ��ȯ
int samePosition(COORD a, COORD b);

// num���� �ּ� minNum���� �ִ� maxNum ������ ������ ��ȯ�Ѵ�.
//
// ��, minNum���� ������ minNum, maxNum���� ũ�� maxNum�� �ȴ�.
int rangedNum(int num, int minNum, int maxNum);

// before���� after���� ���� ������ ��ȯ�Ѵ�. 
//
// �ݵ�� �� �� ���̰� ���� ����� �ϳ����� �Ѵ�.
Direction getDirectionFrom(COORD before, COORD start);

int inRangeRect(COORD point, SMALL_RECT range);

Direction turnRightDirection(Direction direction);
Direction turnLeftDirection(Direction direction);
Direction reverseDirection(Direction direction);

// coord ��ġ�� direction �������� �̵���Ų ���� ��ȯ�Ѵ�.
COORD getMovedCoordInDirection(COORD coord, Direction direction);

#endif
