#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"
#include "utils.h"

#include <time.h>

#define INIT_PLAYER_DIRECTION	DIRECTION_RIGHT
#define INIT_PLAYER_POS			1
#define TARGET_VISION_RANGE		1

#define MOB_KILLING_SCORE		10

typedef enum {
	STATE_NORMAL,
	STATE_SUCCESS,
	STATE_ALL_CLEAR,
	STATE_CAUGHTED
} PlayerState;

// 플레이어의 정보를 가지고 있다.
//
// 방향, 위치, 그리고 시야 무제한 아이템에 대한 정보를 갖고 있다.
typedef struct {
	PlayerState state;

	Direction direction;
	Direction prevDirection;

	// 플레이어의 현재 위치 좌표이다.
	// 
	// 초기 위치는 {1,1}이다.
	COORD position;
	// 플레이어의 이전 위치이다.
	COORD prevPosition;

	// 시야 무제한 아이템을 얻은 시간이다.
	//
	// 제한 시간은 UNLIMIT_VISION_DURATION(5)초 이며, 아이템이 
	// 없는 경우 이 값은 -1이다.
	clock_t visionItemAcquiredTime;

	int killingCount;
} Player;


// 플레이어가 도착 지점에 도착했으면 1을 반환한다.
int onReachedTargetPoint(
	const Player* const player,
	const Map* const	map
);

SMALL_RECT getRectFromPlayerPosition(
	const Player* const player,
	const Map* const	map,
	int					diameter
);

SMALL_RECT getPlayerPreviousVisionRect(
	const Player* const player,
	const Map* const	map
);

// 플레이어의 시야 사각형을 반환한다.
SMALL_RECT getPlayerVisionRect(
	const Player* const player,
	const Map* const	map
);

int hasPlayerVisionItem(const Player* const player);

int getVisionItemLeftTimePercent(const Player* const player);

#endif