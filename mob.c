#include "mob.h"

static COORD _getRandomMobPosition(
	const Map* const	map,
	const Player* const player,
	SMALL_RECT			mapRect
)
{
	SMALL_RECT playerVision = getRectFromPlayerPosition(player, map, 7);
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
	SMALL_RECT mapRect = getRectOf(map);
	Mob newMob;
	Direction direction;
	COORD position;
	int speed = getMobMoveDelayPer(stage);
	int i;

	for (i = 0;i < num;++i)
	{
		direction = rand() % 4;
		position = _getRandomMobPosition(map, player, mapRect);

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

int onCaughtPlayer(
	const Player* const		player,
	const Map* const		map
)
{
	int* ptrCell = getMapCellPtrFrom(player->position, map);
	return *ptrCell == FLAG_MOB_VISION;
}

// 이거 수정해야함!!!!!!!!!!!!!!!!!@@@@@@@@@@@@@@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!!
int onKilledByPlayer(
	const Player* const player,
	const Mob* const	mob
)
{
	Direction reversedMobDirection = reverseDirection(mob->direction);

	// 플레이어가 몹을 잡은 경우는
	// 
	// 1. 현재 둘의 위치가 같다.
	// 2. 서로를 마주보고 있지 않고 있다.
	// 
	// 일때 성립한다.
	if (samePosition(player->position, mob->position) 
		&& player->direction != reversedMobDirection)
	{
		return 1;
	}
	return 0;
}