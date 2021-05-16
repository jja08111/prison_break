#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>
#include <stdlib.h> // min, max

void removeCursor(void);

// 커서를 (2x, y) 좌표로 이동시킨다.
void goto2xy(int x, int y);

// 커서를 (2 * position.X, position.Y) 좌표로 이동시킨다.
void gotoPosition(COORD position);

void gotoCenterForAlignString(SMALL_RECT rect, const char* str);

// 같으면 1, 다르면 0을 반환
int samePosition(COORD a, COORD b);

#endif
