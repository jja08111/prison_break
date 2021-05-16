#include "player.h"

int onReachedTargetPoint(const Player* const player, const Map* const map)
{
	return samePosition(player->position, getTargetPosition(map));
}