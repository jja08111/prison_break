#include "big_number.h"
#include "utils.h"
#include "render.h"

#include <stdio.h>

static void drawZero(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy - 1); printf("  ");
	goto2xy(cx - 1, cy); printf("  ");
	goto2xy(cx + 1, cy); printf("  ");
	goto2xy(cx - 1, cy + 1); printf("  ");
	goto2xy(cx + 1, cy + 1); printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawOne(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx, cy - 2);
	printf("  ");
	goto2xy(cx - 1, cy - 1);
	printf("    ");
	goto2xy(cx, cy);
	printf("  ");
	goto2xy(cx, cy + 1);
	printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawTwo(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx + 1, cy - 1);
	printf("  ");
	goto2xy(cx - 1, cy);
	printf("      ");
	goto2xy(cx - 1, cy + 1);
	printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawThree(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx + 1, cy - 1); 
	printf("  ");
	goto2xy(cx - 1, cy); 
	printf("      ");
	goto2xy(cx + 1, cy + 1); 
	printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawFour(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2); printf("  ");
	goto2xy(cx + 1, cy - 2); printf("  ");
	goto2xy(cx - 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy - 1); printf("  ");
	goto2xy(cx - 1, cy); printf("  ");
	goto2xy(cx + 1, cy); printf("  ");
	goto2xy(cx - 1, cy + 1); 
	printf("        ");
	goto2xy(cx + 1, cy + 2);
	printf("  ");
}

static void drawFive(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1); 
	printf("  ");
	goto2xy(cx - 1, cy);
	printf("      ");
	goto2xy(cx + 1, cy + 1); 
	printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawSix(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1);
	printf("  ");
	goto2xy(cx - 1, cy);
	printf("      ");
	goto2xy(cx - 1, cy + 1); printf("  ");
	goto2xy(cx + 1, cy + 1); printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}

static void drawSeven(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy); 
	printf("  ");
	goto2xy(cx + 1, cy + 1); 
	printf("  ");
	goto2xy(cx + 1, cy + + 2);
	printf("  ");
}

static void drawEight(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy - 1); printf("  ");
	goto2xy(cx - 1, cy);
	printf("      ");
	goto2xy(cx - 1, cy + 1); printf("  ");
	goto2xy(cx + 1, cy + 1); printf("  ");
	goto2xy(cx - 1, cy + 2);
	printf("      ");
}


static void drawNine(const COORD* const centerPosition)
{
	int cx = centerPosition->X;
	int cy = centerPosition->Y;

	goto2xy(cx - 1, cy - 2);
	printf("      ");
	goto2xy(cx - 1, cy - 1); printf("  ");
	goto2xy(cx + 1, cy - 1); printf("  ");
	goto2xy(cx - 1, cy);
	printf("      ");
	goto2xy(cx + 1, cy + 1);
	printf("  ");
	goto2xy(cx - 1, cy + +2);
	printf("      ");
}

static void drawSingleDigitNumber(int number, COORD centerPosition)
{
	switch (number)
	{
	case 0:	drawZero(&centerPosition); break;
	case 1: drawOne(&centerPosition); break;
	case 2:	drawTwo(&centerPosition); break;
	case 3:	drawThree(&centerPosition); break;
	case 4:	drawFour(&centerPosition); break;
	case 5:	drawFive(&centerPosition); break;
	case 6:	drawSix(&centerPosition); break;
	case 7:	drawSeven(&centerPosition); break;
	case 8:	drawEight(&centerPosition); break;
	case 9: drawNine(&centerPosition); break;
	}
}

void drawBigNumber(int number, COORD centerPosition)
{
	if (number >= 1000)
		return;

	if (number < 10)
	{
		drawSingleDigitNumber(number, centerPosition);
	}
	else if (number < 100)
	{
		int digit2 = number / 10;
		int digit1 = number % 10;

		drawSingleDigitNumber(
			digit2, 
			(COORD) { centerPosition.X - 2, centerPosition.Y });
		drawSingleDigitNumber(
			digit1,
			(COORD) { centerPosition.X + 2, centerPosition.Y });
	}
	else
	{
		int digit3 = number / 100;
		int digit2 = (number / 10) % 10;
		int digit1 = number % 10;

		drawSingleDigitNumber(
			digit3, 
			(COORD) { centerPosition.X - 4, centerPosition.Y });
		drawSingleDigitNumber(
			digit2, 
			(COORD) { centerPosition.X, centerPosition.Y });
		drawSingleDigitNumber(
			digit1, 
			(COORD) { centerPosition.X + 4, centerPosition.Y });
	}
}

void drawBigNumberWithColor(int number, COORD centerPosition, int color)
{
	textcolor(color, color);
	drawBigNumber(number, centerPosition);
}

void removeBigNumber(COORD centerPosition)
{
	int cx = centerPosition.X;
	int cy = centerPosition.Y;

	goto2xy(cx - 5, cy - 2);
	printf("                      ");
	goto2xy(cx - 5, cy - 1);
	printf("                      ");
	goto2xy(cx - 5, cy);
	printf("                      ");
	goto2xy(cx - 5, cy + 1);
	printf("                        "); // 4 모양을 고려함
	goto2xy(cx - 5, cy + 2);
	printf("                      ");
}

void removeBigNumberWithColor(COORD centerPosition, int color)
{
	textcolor(color, color);
	removeBigNumber(centerPosition);
}