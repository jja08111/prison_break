#ifndef __STAGE_H__
#define __STAGE_H__

#define MAX_LEVEL 4

// 스테이지 정보를 가지고 있다.
//
// 멤버변수로 level, visionRange, timeLimit가 있다.
typedef struct {
	// 스테이지 레벨이다. 
	//
	// 0부터 시작한다.
	int level;
	
	// 시야 범위이다.
	//
	// 초기 값은 10이다.
	int visionRange;

	// 시간 제한이다.
	int timeLimit;
} Stage;

void initStage(Stage* stage);

// 0단계 10
// 1단계 8
// 2단계 6
// 3단계 4
// 4단계 2 
int visionRangeOf(const Stage* const stage);

// 0단계 60
// 1단계 80
// 2단계 100
// 3단계 120
// 4단계 140 
int timeLimitOf(const Stage* const stage);

void levelUpStage(Stage* stage);

#endif