#ifndef __UTILS_H__
#define __UTILS_H__

#include <Windows.h>

void removeCursor(void);

// (y,2x) ��ġ�� �̵��Ѵ�.
void goto2xy(int x, int y);

void gotoPosition(COORD position);

// ������ 1, �ٸ��� 0�� ��ȯ
int samePosition(COORD a, COORD b);

#endif
