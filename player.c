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

SMALL_RECT getRectFromPlayerPosition(
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

static COORD _getVisionEndPosition(
	COORD			 startPosition,
	Direction		 direction,
	const Map* const map
)
{
	COORD result = startPosition;

	while (canPlace(result, map))
	{
		result = getMovedCoordInDirection(result, direction);
	}
	return result;
}

static SMALL_RECT _getVisionRange(
	COORD			 startPosition,
	Direction		 direction,
	const Map* const map,
	int padding
)
{
	COORD topLeft, bottomRight;
	COORD endOfVision = _getVisionEndPosition(startPosition, direction, map);

	switch (direction)
	{
	case DIRECTION_UP:
		topLeft = (COORD){ endOfVision.X - padding , endOfVision.Y };
		bottomRight = (COORD){ startPosition.X + padding, startPosition.Y + padding };
		break;
	case DIRECTION_DOWN:
		topLeft = (COORD){ startPosition.X - padding, startPosition.Y - padding };
		bottomRight = (COORD){ endOfVision.X + padding, endOfVision.Y };
		break;
	case DIRECTION_LEFT:
		topLeft = (COORD){ endOfVision.X, endOfVision.Y - padding };
		bottomRight = (COORD){ startPosition.X + padding, startPosition.Y + padding };
		break;
	case DIRECTION_RIGHT:
		topLeft = (COORD){ startPosition.X - padding, startPosition.Y - padding };
		bottomRight = (COORD){ endOfVision.X, endOfVision.Y + padding };
	}
	return (SMALL_RECT) { 
		topLeft.X, topLeft.Y,
		bottomRight.X, bottomRight.Y
	};
}

SMALL_RECT getPlayerPreviousVisionRect(
	const Player* const player,
	const Map* const	map
)
{
	return _getVisionRange(player->prevPosition, player->prevDirection, map, 1);
}

SMALL_RECT getPlayerVisionRect(
	const Player* const player,
	const Map* const	map
)
{
	return _getVisionRange(player->position, player->direction, map, 1);
}