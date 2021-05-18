#ifndef __STAGE_H__
#define __STAGE_H__

#define MAX_LEVEL 4

// 스테이지 정보를 가지고 있다.
//
// 멤버변수로 level, score, timeLimit가 있다.
typedef struct {
	// 스테이지 레벨이다. 
	//
	// 0부터 시작한다.
	int level;
	
	// 현재 획득한 점수이다.
	int score;

	// 시간 제한이다.
	int timeLimit;
} Stage;

// 0단계 60
// 1단계 80
// 2단계 100
// 3단계 120
// 4단계 140 
int getTimeLimitPer(const Stage* const stage);

#endif