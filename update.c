#include "update.h"

void updatePosition(COORD* position, const Map* const map, unsigned char keybdInput)
{
	COORD newPosition = *position;

	// ���ο� ��ġ�� �̵�
	switch (keybdInput) {
	case KEYBD_UP: newPosition.Y--; break;
	case KEYBD_DOWN: newPosition.Y++; break;
	case KEYBD_LEFT: newPosition.X--; break;
	case KEYBD_RIGHT: newPosition.X++; break;
	}

	//if (canPlace(newPosition, map))
	//{
		*position = newPosition;
	//}
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
	// ��ǥ�� ������ ���
	if (onReachedTargetPoint(player, map))
	{
		Sleep(DIALOG_DELAY);
		_setNextStage(stage, player, map);
		*newPosition = player->position;
	}
	
	player->prevPosition = player->position;
	if (!samePosition(*newPosition, player->position))
	{
		player->position = *newPosition;
	}
}