#include "stage.h"

int getStageTimeLimit(const Stage* const stage)
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

int getStageStartScore(const Stage* const stage)
{
	return 1000 * (stage->level + 1);
}

static int _getMinimumScore(const Stage* const stage)
{
	switch (stage->level)
	{
	case 0: return 100;
	case 1: return 300;
	case 2: return 500;
	case 3: return 700;
	case MAX_LEVEL: return 1000;
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