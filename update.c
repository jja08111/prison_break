#include "update.h"

Direction updatePosition(COORD* position, const Map* const map, unsigned char keybdInput)
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

static void _setNextStage(Stage* stage, Player* player, Map* map)
{
	stage->level++;
	stage->timeLimit = timeLimitOf(stage);

	player->visionRange = visionRangeOf(stage);
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };

	initMap(map, stage);

	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	system("cls");
}

void update(Stage* stage, Player* player, Map* map, COORD* newPosition)
{
	// 목표에 도달한 경우
	if (onReachedTargetPoint(player, map))
	{
		Sleep(DIALOG_DURATION);
		_setNextStage(stage, player, map);
		*newPosition = player->position;
	}

	player->prevPosition = player->position;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
	}
}