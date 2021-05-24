#ifndef __BOT_H__
#define __BOT_H__

#include "utils.h"
#include "map.h"
#include "player.h"

#include <time.h>

#define MAX_MOB_NUM		100
#define MAX_MOB_SPEED	200

// �����̴� ��ü�̸� �÷��̾ ���ؾ� �� ����̴�.
//
// ����� ��ġ�� ������ �ִ�.
typedef struct {
	// ���� �����̴�.
	Direction direction;
	
	Direction prevDirection;

	// ���� ���� ��ġ�̴�.
	COORD position;

	COORD prevPosition;

	// ���� �ӵ��� ������ �����ð��̴�.
	//
	// �ּ� 200�̴�.
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

// num ���� ��ŭ �߰��� ���� �����Ѵ�.
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

// ���� �þ߿� �� �÷��̾ �������� ��ȯ�Ѵ�.
int onCaughtedPlayer(
	const Player* const		player,
	const Map* const		map
);

// ������ �ڿ��� �����ϴ� ��� ���� �״´�.
int onKilledByPlayer(
	const Player* const player,
	const Mob* const	mob
);

#endif // !__BOT_H__