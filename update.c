#include "update.h"

Direction updatePositionByInput(
	COORD*				position, 
	const Map* const	map, 
	unsigned char		keybdInput
)
{
	COORD newPosition = *position;
	Direction direction;

	// ���ο� ��ġ�� �̵�
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
	case STATE_CAUGHTED:
		// TODO: Implement this
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
	Player*			 player,
	COORD*			 newPosition,
	Direction*		 newDirection,
	Map*			 map,
	SoundController* soundController
)
{
	clock_t now = clock();

	if (onCaughtedPlayer(player, map))
	{
		player->state = STATE_CAUGHTED;
		setSirenSound(soundController);
	}
	if (onReachedTargetPoint(player, map))
	{
		player->state = STATE_SUCCESS;
		setSuccessSound(soundController);
	}

	player->prevDirection = player->direction;
	player->prevPosition = player->position;
	
	player->direction = *newDirection;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
	}

	// ������ �Ⱓ�� ����� ���
	if (hasPlayerVisionItem(player) && 
		now - player->visionItemAcquiredTime > VISION_ITEM_DURATION)
	{
		player->visionItemAcquiredTime = VISION_ITEM_EMPTY;
		map->hasDrawedEntireMap = 0;
		drawEntireMapWith(map, DARK_GRAY);
		renderPlayer(player, map);

		setHeartBeatLoopSound(soundController);
	}

	// �þ� ������ �������� ���� ���
	if(map->grid[newPosition->Y][newPosition->X] == FLAG_UNLIMIT_VISION_ITEM) 
	{
		player->visionItemAcquiredTime = now;
		map->grid[newPosition->Y][newPosition->X] = FLAG_EMPTY;

		setEarningItemSound(soundController);
	}
}

// ���� �̵��ñ��. 
//
// �ַ� ���� ���ϰ� �ִ� ���� Ȥ�� �� ������ �¿�� �����̸�
// �ڷ� ���� �̵��Ѵ�. ���ٸ� �濡 ������ ��� �ڷ� �̵��Ѵ�.
void updateMobPosition(
	Mob*			 mob,
	const Map* const map
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

		// 1% Ȯ���� �ڷ� ���� �̵��Ѵ�.
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

// �÷��׸� ���� �׸��忡 �����Ѵ�.
//
// position ��ġ���� direction �������� ���� ���� ������ 
// �ݺ��Ͽ� flag�� ĭ�� �ʱ�ȭ�Ѵ�.
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
	// ���� ��ġ�� �÷��״� �����.
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
	const Map* const	map,
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
	_updatePlayer(player, newPlayerPosition, newDirection, map, soundController);
	_updateMob(mobHandler, player, map, soundController);

	_updateSound(soundController);
}