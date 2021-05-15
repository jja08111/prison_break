#include "update.h"

void updatePlayerPosition(Player* player, const Map* const map, unsigned char keybdInput)
{
	COORD newPosition = player->position;

	// 새로운 위치로 이동
	switch (keybdInput) {
	case KEYBD_UP: newPosition.Y--; break;
	case KEYBD_DOWN: newPosition.Y++; break;
	case KEYBD_LEFT: newPosition.X--; break;
	case KEYBD_RIGHT: newPosition.X++; break;
	}

	if (canPlace(newPosition, map))
	{
		player->prevPosition = player->position;
		player->position = newPosition;
	}
}

static void _levelUpStage(Stage* stage)
{

}

void update(Stage* stage, Player* player, Map* map)
{

}