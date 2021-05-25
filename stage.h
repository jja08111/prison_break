#ifndef __STAGE_H__
#define __STAGE_H__

#include <time.h>

#define MAX_LEVEL				4
#define SCORE_UPDATE_INTERVAL	1000 //1000�и���
#define SCORE_DECREASE_INTERVAL 10	

// �������� ������ ������ �ִ�.
//
// ��������� level, score, timeLimit�� �ִ�.
typedef struct {
	// �������� �����̴�. 
	//
	// 0���� �����Ѵ�.
	int level;
	
	// ������������ ȹ�� ������ �����̴�.
	//
	// �ð��� �������� �����ϸ� �ּ� ���� 100�̴�.
	int score;

	clock_t scoreUpdateTime;

	int totalScore;

	// �ð� �����̴�.
	int timeLimit;
} Stage;

// 0�ܰ� 60
// 1�ܰ� 80
// 2�ܰ� 100
// 3�ܰ� 120
// 4�ܰ� 140 
int getStageTimeLimit(const Stage* const stage);

int getStageStartScore(const Stage* const stage);

static int _getMinimumScore(const Stage* const stage);

void decreaseScore(Stage* stage);

#endif