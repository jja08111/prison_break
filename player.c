#include "player.h"

int getPlayerVisionRangePer(const Stage* const stage)
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

SMALL_RECT getRectFromPlayer(
	const Player* const player,
	const Map* const	map,
	int					halfDiameter
)
{
	COORD position = player->position;

	int top = position.Y - halfDiameter;
	int bottom = position.Y + halfDiameter;
	int left = position.X - halfDiameter;
	int right = position.X + halfDiameter;

	return (SMALL_RECT) {
		rangedNum(left, 0, map->width),
			rangedNum(top, 0, map->height),
			rangedNum(right, 0, map->width),
			rangedNum(bottom, 0, map->height)
	};
}

SMALL_RECT getPlayerVisionRect(
	const Player* const player,
	const Map* const	map
)
{
	return getRectFromPlayer(player, map, player->visionRange);
}