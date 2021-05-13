#include "player.h"

void _gotoPosition(COORD position)
{
	goto2xy(position.X, position.Y);
}

void initPlayer(Player* player) 
{
	player->position = (COORD){ 1,1 };
	player->life = 5;
	player->score = 0;
}

void printPlayer(const Player* const player)
{
	_gotoPosition(player->position);
	printPlayerIcon();
}

void movePlayer(Player* player, const Map* const map, unsigned char keybdInput)
{
	COORD prevPosition = player->position;

	// 새로운 위치로 이동
	switch (keybdInput) {
	case KEYBD_UP: player->position.Y--; break;
	case KEYBD_DOWN: player->position.Y++; break;
	case KEYBD_LEFT: player->position.X--; break;
	case KEYBD_RIGHT: player->position.X++; break;
	}

	if (!canPlace(player->position, map)) {
		player->position = prevPosition;
		return;
	}

	// 이전 위치의 아이콘을 지운다.
	_gotoPosition(prevPosition);
	printEmptyIcon();
	// 새로운 위치에 아이콘을 그린다.
	printPlayer(player);
}