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

	// ���ο� ��ġ�� �̵�
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

	// ���� ��ġ�� �������� �����.
	_gotoPosition(prevPosition);
	printEmptyIcon();
	// ���ο� ��ġ�� �������� �׸���.
	printPlayer(player);
}