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

// 커서를 (2x, y) 좌표로 이동시킨다.
void goto2xy(int x, int y);

// 커서를 (2 * position.X, position.Y) 좌표로 이동시킨다.
void gotoPosition(COORD position);

// x 값은 2칸을 한 칸으로 두어 계산한다.
void gotoCenterForAlignString(
	SMALL_RECT	rect, 
	const char* str
);

// 같으면 1, 다르면 0을 반환
int samePosition(COORD a, COORD b);

// num값을 최소 minNum에서 최대 maxNum 사이의 값으로 반환한다.
//
// 즉, minNum보다 작으면 minNum, maxNum보다 크면 maxNum이 된다.
int rangedNum(int num, int minNum, int maxNum);

// before에서 after로의 진행 방향을 반환한다. 
//
// 반드시 두 값 차이가 나는 멤버가 하나여야 한다.
Direction getDirectionFrom(COORD before, COORD start);

int inRangeRect(COORD point, SMALL_RECT range);

Direction turnRightDirection(Direction direction);
Direction turnLeftDirection(Direction direction);
Direction reverseDirection(Direction direction);

// coord 위치를 direction 방향으로 이동시킨 값을 반환한다.
COORD getMovedCoordInDirection(COORD coord, Direction direction);

#endif
