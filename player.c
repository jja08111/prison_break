#include "player.h"

int visionRangeOf(const Stage* const stage)
{
	switch (stage->level) {
	case 0: return 16;
	case 1: return 12;
	case 2: return 8;
	case 3: return 4;
	case MAX_LEVEL: return 2;
	}
	return 0;
}

int onReachedTargetPoint(
	const Player* const player, 
	const Map* const	map
)
{
	return samePosition(player->position, getTargetPosition(map));
}