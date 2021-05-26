#include "stage.h"

int getStageStartScore(const Stage* const stage)
{
	switch (stage->level)
	{
	case 0: return 30;
	case 1: return 60;
	case 2: return 100;
	case 3: return 150;
	case MAX_LEVEL: return 200;
	}
	return 0;
}

static int _getMinimumScore(const Stage* const stage)
{
	switch (stage->level)
	{
	case 0: return 5;
	case 1: return 10;
	case 2: return 15;
	case 3: return 20;
	case MAX_LEVEL: return 30;
	}
	return 0;
}

void decreaseScore(Stage* stage)
{
	int minScore = _getMinimumScore(stage);
	int result = stage->score - SCORE_DECREASE_INTERVAL;
	
	if (result >= minScore)
	{
		stage->score = result;
	}
}