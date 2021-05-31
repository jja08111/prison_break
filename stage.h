#ifndef __STAGE_H__
#define __STAGE_H__

#include <time.h>

#define MAX_LEVEL				4
#define SCORE_UPDATE_INTERVAL	1000 //1000�и���
#define SCORE_DECREASE_INTERVAL 1	

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
	int prevScore;

	clock_t scoreUpdateTime;

	int totalScore;
	int prevTotalScore;
} Stage;

int getStageStartScore(const Stage* const stage);

void decreaseScore(Stage* stage);

#endif