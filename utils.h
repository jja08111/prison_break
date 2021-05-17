#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>
#include <stdlib.h> // min, max

typedef enum _Direction {
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN, 
	DIRECTION_RIGHT
} Direction;

static void _gotoxy(int x, int y);

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

Direction getDirectionFrom(COORD start, COORD end);

#endif
