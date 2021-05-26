#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <Windows.h>

void drawBigNumber(int number, COORD centerPosition);
void drawBigNumberWithColor(int number, COORD centerPosition, int color);

void removeBigNumber(COORD centerPosition);
void removeBigNumberWithColor(COORD centerPosition, int color);

#endif