#include "mob.h"

static COORD _getRandomMobPosition(
	const Map* const	map,
	const Player* const player,
	SMALL_RECT			mapRect
)
{
	SMALL_RECT playerVision = getRectFromPlayer(player, map, 7);
	COORD result;
	int loY, hiY;
	int loX, hiX;

	do {
		loY = max(mapRect.Top, 1);
		hiY = mapRect.Bottom - 1;

		loX = max(mapRect.Left, 1);
		hiX = mapRect.Right - 1;

		result.Y = rand() % (hiY - loY + 1) + loY;
		result.X = rand() % (hiX - loX + 1) + loX;
	} while (!canPlace(result, map) 
		|| inRangeRect(result, playerVision));
	
	return result;
}

int getMobMoveDelayPer(const Stage* const stage)
{
	switch (stage->level) 
	{
	case 0: return 400;
	case 1: return 360;
	case 2: return 320;
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
	SMALL_RECT mapRect = getRectOf(map);
	Mob newMob;
	COORD position;
	int speed = getMobMoveDelayPer(stage);
	int i;

	for (i = 0;i < num;++i)
	{
		position = _getRandomMobPosition(map, player, mapRect);

		newMob = (Mob){ 
			rand() % 4,
			position,
			position,
			speed 
		};
		insertMobAtLast(mobHandler, newMob);
	}
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
	mob->direction = getDirectionFrom(mob->position, targetPosition);

	mob->prevPosition = mob->position;
	mob->position = targetPosition;
}