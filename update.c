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

	player->visionRange = getPlayerVisionRangePer(stage);
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };

	initMap(map, stage);

	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	system("cls");
}

static void _handleStageSuccess(
	Stage*	stage,
	Player* player,
	Map*	map,
	COORD*	newPosition
)
{
	Sleep(DIALOG_DURATION);
	_setNextStage(stage, player, map);
	*newPosition = player->position;
}

static void _updatePlayer(
	Player*		player,
	COORD*		newPosition,
	Direction*	newDirection
)
{
	player->prevDirection = player->direction;
	player->prevPosition = player->position;
	
	player->direction = *newDirection;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
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

	COORD goStraightPosition = moveInDirection(mob->position, mob->direction);
	COORD goLeftPosition = moveInDirection(mob->position, turnLeftDirection(mob->direction));
	COORD goRightPosition = moveInDirection(mob->position, turnRightDirection(mob->direction));
	COORD goBackPosition = moveInDirection(mob->position, turnBackDirection(mob->direction));

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

static void _updateMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Map* const	map
) 
{
	static clock_t prevClock = 0;
	clock_t now = clock();
	int i;

	for (i = 0;i < mobHandler->count;++i)
	{
		Mob* currentMob = &mobHandler->arrMob[i];

		if (now - prevClock > currentMob->moveDelay)
		{
			_updateMobPosition(currentMob, player, map);
			
			if(i == mobHandler->count - 1)
				prevClock = now;
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
	// 목표에 도달한 경우
	if (onReachedTargetPoint(player, map))
	{
		_handleStageSuccess(stage, player, map, newPlayerPosition);
	}

	_updatePlayer(player, newPlayerPosition, newDirection);

	_updateMob(mobHandler, player, map);
}