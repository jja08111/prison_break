#ifndef __BOT_H__
#define __BOT_H__

#include "utils.h"
#include "map.h"
#include "player.h"

#define INIT_MOB_NUM	4
#define MAX_MOB_NUM		100

// 움직이는 객체이며 플레이어가 제거할 대상이다.
//
// 방향과 위치를 가지고 있다.
typedef struct {
	// 봇의 방향이다.
	Direction direction;

	// 봇의 현재 위치이다.
	COORD position;

	COORD prevPosition;
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

// num 개수 만큼 추가로 봇을 생성한다.
void generateMob(
	MobHandler*			mobHandler,
	int					num,
	const Player* const player,
	const Map* const	map
);

void insertMobAtLast(MobHandler* mobHandler, Mob mob);

void moveMobTo(
	Mob*	mob,
	COORD	position
);

#endif // !__BOT_H__