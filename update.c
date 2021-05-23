#include "update.h"

Direction updatePositionByInput(
	COORD*				position, 
	const Map* const	map, 
	unsigned char		keybdInput
)
{
	COORD newPosition = *position;
	Direction direction;

	// 새로운 위치로 이동
	switch (keybdInput) {
	case KEYBD_UP:
		newPosition.Y--;
		direction = DIRECTION_UP;
		break;
	case KEYBD_DOWN: 
		direction = DIRECTION_DOWN;
		newPosition.Y++;
		break;
	case KEYBD_LEFT: 
		direction = DIRECTION_LEFT;
		newPosition.X--; 
		break;
	case KEYBD_RIGHT:
		direction = DIRECTION_RIGHT;
		newPosition.X++;
		break;
	}

	if (canPlace(newPosition, map))
	{
		*position = newPosition;
	}
	
	return direction;
}

static void _setNextStage(
	Stage*	stage,
	Player* player,
	Map*	map
)
{
	stage->level++;
	stage->timeLimit = getTimeLimitPer(stage);

	player->state = STATE_NORMAL;
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };

	initMap(map, stage);

	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	system("cls");
}

static void _updateStage(
	Stage*	stage, 
	Player*	player,
	COORD*	newPosition,
	Map*	map
)
{
	switch (player->state)
	{
	case STATE_CAUGHTED:
	case STATE_SUCCESS:
		_setNextStage(stage, player, map);
		*newPosition = player->position;
		break;
	default:
		break;
	}
}

static void _updatePlayer(
	Player*		player,
	COORD*		newPosition,
	Direction*	newDirection,
	Map*		map
)
{
	clock_t now = clock();

	if (onCaughtedPlayer(player, map))
	{
		player->state = STATE_CAUGHTED;
	}
	if (onReachedTargetPoint(player, map))
	{
		player->state = STATE_SUCCESS;
	}

	player->prevDirection = player->direction;
	player->prevPosition = player->position;
	
	player->direction = *newDirection;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
	}

	// 아이템 기간이 만료된 경우
	if (hasPlayerVisionItem(player) 
		&& now - player->visionItemAcquiredTime > VISION_ITEM_DURATION)
	{
		player->visionItemAcquiredTime = VISION_ITEM_EMPTY;
		map->hasDrawedEntireMap = 0;
		drawEntireMapWith(map, DARK_GRAY);
		renderPlayer(player, map);
	}

	// 시야 무제한 아이템을 먹은 경우
	if(map->grid[newPosition->Y][newPosition->X] == FLAG_UNLIMIT_VISION_ITEM) 
	{
		player->visionItemAcquiredTime = now;
		map->grid[newPosition->Y][newPosition->X] = FLAG_EMPTY;
	}
}

// 몹을 이동시긴다. 
//
// 주로 현재 향하고 있는 방향 혹은 그 방향의 좌우로 움직이며
// 뒤로 가끔 이동한다. 막다른 길에 도달한 경우 뒤로 이동한다.
static void _updateMobPosition(
	Mob*				mob,
	const Player* const player,
	const Map* const	map
) 
{
	int randomNum, randomForGoBack;
	int highPriorityPositionCount = 0;
	int canGoBack = 0;
	COORD highPriorityPosition[3];

	COORD goStraightPosition = getMovedCoordInDirection(mob->position, mob->direction);
	COORD goLeftPosition = getMovedCoordInDirection(mob->position, turnLeftDirection(mob->direction));
	COORD goRightPosition = getMovedCoordInDirection(mob->position, turnRightDirection(mob->direction));
	COORD goBackPosition = getMovedCoordInDirection(mob->position, reverseDirection(mob->direction));

	if (canPlace(goStraightPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = goStraightPosition;
	}
	if (canPlace(goLeftPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = goLeftPosition;
	}
	if (canPlace(goRightPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = goRightPosition;
	}
	if (canPlace(goBackPosition, map))
	{
		canGoBack = 1;
	}

	if (highPriorityPositionCount > 0)
	{
		randomNum = rand() % highPriorityPositionCount;
		randomForGoBack = rand() % 101;

		// 1% 확률로 뒤로 돌아 이동한다.
		if(randomForGoBack < 1)
			moveMobTo(mob, goBackPosition);
		else 
			moveMobTo(mob, highPriorityPosition[randomNum]);
	}
	else
	{
		moveMobTo(mob, goBackPosition);
	}
}

// 플래그를 맵의 그리드에 설정한다.
//
// position 위치부터 direction 방향으로 벽을 만날 때까지 
// 반복하여 flag를 칸에 초기화한다.
static void _setVisionFlagToMap(
	COORD				position,
	Direction			direction,
	MapFlag				flag,
	const Map* const	map
)
{
	int* ptrCell;

	while (canPlace(position, map))
	{
		ptrCell = getMapCellPtrFrom(position, map);
		*ptrCell = flag;

		position = getMovedCoordInDirection(position, direction);
	}
}

static void _clearVisionFlagToMap(
	COORD			 position,
	Direction		 direction,
	const Map* const map
)
{
	_setVisionFlagToMap(position, direction, FLAG_EMPTY, map);
}

static void _updateMobVisionFlagToMap(
	const Mob* const mob,
	const Map* const map
)
{
	int* ptrCell = getMapCellPtrFrom(mob->prevPosition, map);
	// 이전 위치의 플래그는 지운다.
	*ptrCell = FLAG_EMPTY;

	if (mob->direction != mob->prevDirection)
	{
		_clearVisionFlagToMap(mob->prevPosition, mob->prevDirection, map);
	}

	_setVisionFlagToMap(mob->position, mob->direction, FLAG_MOB_VISION, map);
}

static void _removeMob(
	const Mob* const	mob,
	const Player* const player,
	const Map* const	map
)
{
	COORD startPosition = getMovedCoordInDirection(mob->position, mob->direction);

	textcolor(SURFACE_COLOR, SURFACE_COLOR);
	drawMobVisionInPlayerRange(startPosition, mob->direction, map, player);

	_clearVisionFlagToMap(mob->position, mob->direction, map);
}

static void _updateMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Map* const	map
) 
{
	clock_t now = clock();
	int i;

	for (i = 0;i < mobHandler->count;++i)
	{
		Mob* currentMob = &mobHandler->arrMob[i];

		if (currentMob->wasKilled)
			continue;

		if (onKilledByPlayer(player, currentMob))
		{
			_removeMob(currentMob, player, map);
			currentMob->wasKilled = 1;
			continue;
		}

		_updateMobVisionFlagToMap(currentMob, map);

		if (now - currentMob->updatedClock > currentMob->moveDelay)
		{
			_updateMobPosition(currentMob, player, map);
			
			currentMob->updatedClock = now;
		}
	}	
}

void update(
	Stage*		stage,
	Player*		player,
	MobHandler* mobHandler,
	Map*		map,
	COORD*		newPlayerPosition,
	Direction*	newDirection
)
{
	_updateStage(stage, player, newPlayerPosition, map);
	_updatePlayer(player, newPlayerPosition, newDirection, map);
	_updateMob(mobHandler, player, map);
}