#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"
#include "utils.h"

#define INIT_PLAYER_POS 1
#define TARGET_VISION_RANGE 2

enum VisionPattern { VISION_DEFAULT };

// 플레이어의 정보를 가지고 있다.
//
// 멤버변수로 position, life, score를 가지고 있다. 이때 position은 COORD 구조체이며,
// 이 구조체는 멤버변수로 X,Y를 가지고 있다.
typedef struct {
	Direction direction;
	Direction prevDirection;
	// 플레이어의 현재 위치 좌표이다.
	// 
	// 초기 위치는 {1,1}이다.
	COORD position;

	// 플레이어의 이전 위치이다.
	COORD prevPosition;

	short life;

	short visionRange;

	enum VisionPattern visionPattern;
} Player;

// 0단계 10
// 1단계 8
// 2단계 6
// 3단계 4
// 4단계 2 
int visionRangeOf(const Stage* const stage);

int onReachedTargetPoint(const Player* const player, const Map* const map);


#endif