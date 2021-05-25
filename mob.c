#include "mob.h"

static COORD _getRandomMobPosition(
	const Map* const	map,
	const Player* const player
)
{
	SMALL_RECT playerVision = getRectFromPlayerPosition(player, map, 7);
	COORD result;

	do {
		result.X = OBJECT_GEN_PADDING + rand() % (map->width - OBJECT_GEN_PADDING * 2);
		result.Y = OBJECT_GEN_PADDING + rand() % (map->height - OBJECT_GEN_PADDING * 2);

		// 홀수 칸에만 배치한다.
		if (result.X % 2 == 0)
			result.X--;
		if (result.Y % 2 == 0)
			result.Y--;
	} while (!canPlace(result, map) 
		|| inRangeRect(result, playerVision));
	
	return result;
}

int getMobCountPer(const Stage* const stage)
{
	switch (stage->level)
	{
	case 0: return 4;
	case 1: return 6;
	case 2: return 8;
	case 3: return 10;
	case MAX_LEVEL: return 12;
	}
	return 0;
}

int getMobMoveDelayPer(const Stage* const stage)
{
	switch (stage->level) 
	{
	case 0: return 600;
	case 1: return 460;
	case 2: return 340;
	case 3: return 260;
	case MAX_LEVEL: return 200;
	}
	return 0;
}

void generateMob(
	MobHandler*			mobHandler,
	int					num,
	const Player* const player,
	const Stage* const	stage,
	const Map* const	map
)
{
	SMALL_RECT mapRect = getMapRect(map);
	Mob newMob;
	Direction direction;
	COORD position;
	int speed = getMobMoveDelayPer(stage);
	int i;

	for (i = 0;i < num;++i)
	{
		direction = rand() % 4;
		position = _getRandomMobPosition(map, player);

		newMob = (Mob){ 
			direction,
			direction,
			position,
			position,
			speed,
			0,
			0
		};
		insertMobAtLast(mobHandler, newMob);
	}
}

void clearMob(MobHandler* mobHandler)
{
	memset(mobHandler, 0, sizeof(MobHandler));
}

void insertMobAtLast(MobHandler* mobHandler, Mob mob)
{
	if (mobHandler->count == MAX_MOB_NUM)
		return;
	mobHandler->arrMob[mobHandler->count++] = mob;
}

void moveMobTo(
	Mob*	mob,
	COORD	targetPosition
)
{
	mob->prevDirection = mob->direction;
	mob->direction = getDirectionFrom(mob->position, targetPosition);

	mob->prevPosition = mob->position;
	mob->position = targetPosition;
}

int onCaughtedPlayer(
	const Player* const		player,
	const Map* const		map
)
{
	int* ptrCell = getMapCellPtrFrom(player->position, map);
	return *ptrCell == FLAG_MOB_VISION;
}

int onKilledByPlayer(
	const Player* const player,
	const Mob* const	mob
)
{
	// 플레이어가 몹을 잡은 경우는
	// 
	// 1. 플레이어가 잡히지 않았다.
	// 2. 플레이어가 움직였다.
	// 3. 현재 둘의 위치가 같다.
	// 
	// 일때 성립한다.
	if (player->state != STATE_CAUGHTED &&
		!samePosition(player->prevPosition, player->position) && 
		samePosition(player->position, mob->position))
	{
		return 1;
	}
	return 0;
}