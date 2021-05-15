#include "stage.h"

int visionRangeOf(const Stage* const stage)
{
	switch (stage->level) {
	case 0: return 10;
	case 1: return 8;
	case 2: return 6;
	case 3: return 4;
	case MAX_LEVEL: return 2;
	}
	return 0;
}

int timeLimitOf(const Stage* const stage)
{
	switch (stage->level)
	{
	case 0: return 60;
	case 1: return 80;
	case 2: return 100;
	case 3: return 120;
	case MAX_LEVEL: return 140;
	}
	return 0;
}