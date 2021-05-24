#ifndef __BOT_H__
#define __BOT_H__

#include "utils.h"
#include "map.h"
#include "player.h"

#include <time.h>

#define MAX_MOB_NUM		100
#define MAX_MOB_SPEED	200

// 움직이는 객체이며 플레이어가 피해야 할 대상이다.
//
// 방향과 위치를 가지고 있다.
typedef struct {
	// 몹의 방향이다.
	Direction direction;
	
	Direction prevDirection;

	// 몹의 현재 위치이다.
	COORD position;

	COORD prevPosition;

	// 몹의 속도를 결정할 지연시간이다.
	//
	// 최소 200이다.
	int moveDelay;

	clock_t updatedClock;

	int wasKilled;
} Mob;

typedef struct {
	Mob arrMob[MAX_MOB_NUM];

	int count;

} MobHandler;


static COORD _getRandomMobPosition(
	const Map* const	map,
	const Player* const player,
	SMALL_RECT			rect
);

int getMobCountPer(const Stage* const stage);

int getMobMoveDelayPer(const Stage* const stage);

// num 개수 만큼 추가로 봇을 생성한다.
void generateMob(
	MobHandler*			mobHandler,
	int					num,
	const Player* const player,
	const Stage* const	stage,
	const Map* const	map
);

void clearMob(MobHandler* mobHandler);

void insertMobAtLast(MobHandler* mobHandler, Mob mob);

void moveMobTo(
	Mob*	mob,
	COORD	position
);

// 몹의 시야에 들어서 플레이어가 잡혔는지 반환한다.
int onCaughtedPlayer(
	const Player* const		player,
	const Map* const		map
);

// 유저가 뒤에서 접근하는 경우 몹은 죽는다.
int onKilledByPlayer(
	const Player* const player,
	const Mob* const	mob
);

#endif // !__BOT_H__