#include "stage.h"

int getTimeLimitPer(const Stage* const stage)
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