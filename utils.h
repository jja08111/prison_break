#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>

#define MIN(a,b) (((a)<(b)) ? (a) : (b))
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

void removeCursor(void);

// (y,2x) ��ġ�� �̵��Ѵ�.
void goto2xy(int x, int y);

void gotoPosition(COORD position);

// ������ 1, �ٸ��� 0�� ��ȯ
int samePosition(COORD a, COORD b);

#endif
