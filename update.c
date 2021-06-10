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
	Stage*			 stage,
	Player*			 player,
	Map*			 map,
	MobHandler*		 mobHandler
)
{
	stage->level++;

	stage->totalScore += stage->score;
	stage->score = getStageStartScore(stage);

	player->visionItemAcquiredTime = VISION_ITEM_EMPTY;
	player->state = STATE_NORMAL;
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };

	initMap(map, stage);

	clearMob(mobHandler);
	generateMob(mobHandler, getMobCountPer(stage), player, stage, map);

	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	system("cls");
}

static void _updateStage(
	Stage*			 stage, 
	Player*			 player,
	COORD*			 newPosition,
	Map*			 map,
	MobHandler*		 mobHandler,
	SoundController* soundController
)
{
	clock_t now = clock();

	switch (player->state)
	{
	case STATE_SUCCESS:
		_setNextStage(stage, player, map, mobHandler);
		setHeartBeatLoopSound(soundController);
		*newPosition = player->position;
		break;
	default:
		break;
	}

	if (now - stage->scoreUpdateTime >= SCORE_UPDATE_INTERVAL) 
	{
		decreaseScore(stage);
		stage->scoreUpdateTime = now;
	}
}

static void _updatePlayer(
	Player*				player,
	COORD*				newPosition,
	Direction*			newDirection,
	Map*				map,
	Stage* 				stage,
	SoundController*	soundController
)
{
	clock_t now = clock();

	if (onCaughtedPlayer(player, map))
	{
		player->state = STATE_CAUGHTED;
		setSirenSound(soundController);
	}
	else if (onReachedTargetPoint(player, map))
	{
		if (stage->level == MAX_LEVEL)
		{
			stage->totalScore += stage->score;
			player->state = STATE_ALL_CLEAR;
			setAllClearSound(soundController);
		}
		else
		{
			player->state = STATE_SUCCESS;
			setSuccessSound(soundController);
		}
	}

	player->prevDirection = player->direction;
	player->prevPosition = player->position;
	
	player->direction = *newDirection;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
	}

	// 아이템 기간이 만료된 경우
	if (hasPlayerVisionItem(player) && 
		now - player->visionItemAcquiredTime > VISION_ITEM_DURATION)
	{
		player->visionItemAcquiredTime = VISION_ITEM_EMPTY;
		map->hasDrawedEntireMap = 0;
		drawEntireMapWith(map, DARK_GRAY);
		renderPlayer(player, map);

		setHeartBeatLoopSound(soundController);
	}

	// 시야 무제한 아이템을 먹은 경우
	if(map->grid[newPosition->Y][newPosition->X] == FLAG_UNLIMIT_VISION_ITEM) 
	{
		player->visionItemAcquiredTime = now;
		map->grid[newPosition->Y][newPosition->X] = FLAG_EMPTY;

		setEarningItemSound(soundController);
	}
}

static int canPlaceMob(
	COORD position,
	Map*  map
)
{
	const int* ptrCell = getMapCellPtrFrom(position, map);

	return canPlace(position, map) && *ptrCell != FLAG_TARGET;
}

// 몹을 이동시긴다. 
//
// 주로 현재 향하고 있는 방향 혹은 그 방향의 좌우로 움직이며
// 뒤로 가끔 이동한다. 막다른 길에 도달한 경우 뒤로 이동한다.
void updateMobPosition(
	Mob* mob,
	Map* map
) 
{
	int randomNum, randomForGoBack;
	int highPriorityPositionCount = 0;
	COORD highPriorityPosition[3];

	COORD forwardPosition = getMovedCoordInDirection(mob->position, mob->direction);
	COORD leftPosition = getMovedCoordInDirection(mob->position, turnLeftDirection(mob->direction));
	COORD rightPosition = getMovedCoordInDirection(mob->position, turnRightDirection(mob->direction));
	COORD backPosition = getMovedCoordInDirection(mob->position, reverseDirection(mob->direction));

	if (canPlaceMob(forwardPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = forwardPosition;
	}
	if (canPlaceMob(leftPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = leftPosition;
	}
	if (canPlaceMob(rightPosition, map))
	{
		highPriorityPosition[highPriorityPositionCount++] = rightPosition;
	}

	if (highPriorityPositionCount > 0)
	{
		randomNum = rand() % highPriorityPositionCount;
		randomForGoBack = rand() % 101;

		// 1% 확률로 뒤로 돌아 이동한다.
		if(randomForGoBack < 1)
			moveMobTo(mob, backPosition);
		else 
			moveMobTo(mob, highPriorityPosition[randomNum]);
	}
	else
	{
		moveMobTo(mob, backPosition);
	}
}

// 플래그를 맵의 그리드에 설정한다.
//
// position 위치부터 direction 방향으로 벽을 만날 때까지 
// 반복하여 flag를 칸에 초기화한다.
static void _setVisionFlagToMap(
	COORD		position,
	Direction	direction,
	MapFlag		flag,
	Map*		map
)
{
	int* ptrCell;

	while (canPlace(position, map))
	{
		ptrCell = getMapCellPtrFrom(position, map);
		if(*ptrCell != FLAG_TARGET)
			*ptrCell = flag;

		position = getMovedCoordInDirection(position, direction);
	}
}

static void _clearVisionFlagToMap(
	COORD		position,
	Direction	direction,
	Map*		map
)
{
	_setVisionFlagToMap(position, direction, FLAG_EMPTY, map);
}

static void _updateMobVisionFlagToMap(
	const Mob* const mob,
	Map*			 map
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
	Map*				map
)
{
	COORD startPosition = getMovedCoordInDirection(mob->position, mob->direction);

	textcolor(SURFACE_COLOR, SURFACE_COLOR);
	drawMobVisionInPlayerRange(startPosition, mob->direction, map, player);

	_clearVisionFlagToMap(mob->position, mob->direction, map);
}

static void _updateMob(
	MobHandler*			mobHandler,
	Player*				player,
	Stage*				stage,
	Map* 				map,
	SoundController*	soundController
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

			player->killingCount++;
			stage->totalScore += MOB_KILLING_SCORE;

			setBoneCrushingSound(soundController);
			continue;
		}

		_updateMobVisionFlagToMap(currentMob, map);

		if (now - currentMob->updatedClock > currentMob->moveDelay)
		{
			updateMobPosition(currentMob, map);
			
			currentMob->updatedClock = now;
		}
	}	
}

static void _updateSound(SoundController* controller)
{
	clock_t now = clock();

	if (controller->nextSoundTime != EMPTY_NEXT_SOUND &&
		controller->nextSoundTime <= now)
	{
		controller->currentSound = controller->nextSound;
		controller->currentPlayMode = controller->nextPlayMode;

		controller->isUpdated = 1;

		clearNextSound(controller);
	}

	if (controller->isUpdated)
	{
		controller->isUpdated = 0;
		playSound(controller);
	}
}

void update(
	Stage*			 stage,
	Player*			 player,
	MobHandler*		 mobHandler,
	Map*			 map,
	SoundController* soundController,
	COORD*			 newPlayerPosition,
	Direction*		 newDirection
)
{
	_updateStage(stage, player, newPlayerPosition, map, mobHandler, soundController);
	_updatePlayer(player, newPlayerPosition, newDirection, map, stage, soundController);
	_updateMob(mobHandler, player, stage, map, soundController);

	_updateSound(soundController);
}