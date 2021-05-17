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

void generateMob(
	MobHandler*			mobHandler,
	int					num,
	const Player* const player,
	const Map* const	map
)
{
	SMALL_RECT mapRect = getRectOf(map);
	Mob newMob;
	int i;

	for (i = 0;i < num;++i)
	{
		newMob = (Mob){
			rand() % 4,
			_getRandomMobPosition(map, player, mapRect)
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