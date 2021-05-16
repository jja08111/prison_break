#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>
#include <stdlib.h> // min, max

static void _gotoxy(int x, int y);

void removeCursor(void);

// 커서를 (2x, y) 좌표로 이동시킨다.
void goto2xy(int x, int y);

// 커서를 (2 * position.X, position.Y) 좌표로 이동시킨다.
void gotoPosition(COORD position);

void gotoCenterForAlignString(SMALL_RECT rect, const char* str);

// 같으면 1, 다르면 0을 반환
int samePosition(COORD a, COORD b);

// num값을 최소 minNum에서 최대 maxNum 사이의 값으로 반환한다.
//
// 즉, minNum보다 작으면 minNum, maxNum보다 크면 maxNum이 된다.
int rangedNum(int num, int minNum, int maxNum);

#endif
