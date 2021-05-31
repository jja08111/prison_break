#ifndef __STAGE_H__
#define __STAGE_H__

#include <time.h>

#define MAX_LEVEL				4
#define SCORE_UPDATE_INTERVAL	1000 //1000밀리초
#define SCORE_DECREASE_INTERVAL 1	

// 스테이지 정보를 가지고 있다.
//
// 멤버변수로 level, score, timeLimit가 있다.
typedef struct {
	// 스테이지 레벨이다. 
	//
	// 0부터 시작한다.
	int level;
	
	// 스테이지에서 획득 가능한 점수이다.
	//
	// 시간이 지날수록 감소하며 최소 값은 100이다.
	int score;
	int prevScore;

	clock_t scoreUpdateTime;

	int totalScore;
	int prevTotalScore;
} Stage;

int getStageStartScore(const Stage* const stage);

void decreaseScore(Stage* stage);

#endif