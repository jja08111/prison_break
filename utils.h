#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>

#define MIN(a,b) (((a)<(b)) ? (a) : (b))
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

void removeCursor(void);

// (y,2x) 위치로 이동한다.
void goto2xy(int x, int y);

void gotoPosition(COORD position);

// 같으면 1, 다르면 0을 반환
int samePosition(COORD a, COORD b);

#endif
