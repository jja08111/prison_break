#include "player.h"

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

int hasPlayerVisionItem(const Player* const player)
{
	return player->visionItemAcquiredTime != EMPTY_ITEM;
}

int hasPlayerExhaustItem(const Player* const player)
{
	return player->exhaustItemAcquiredTime != EMPTY_ITEM;
}

int getVisionItemLeftTimePercent(const Player* const player)
{
	if (!hasPlayerVisionItem(player))
		return 0;

	int leftTime = (VISION_ITEM_DURATION - (clock() - player->visionItemAcquiredTime));

	return max(0, leftTime * 100 / VISION_ITEM_DURATION);
}

int getExhaustItemLeftTimePercent(const Player* const player)
{
	if (!hasPlayerExhaustItem(player))
		return 0;

	int leftTime = (EXHAUST_ITEM_DURATION - (clock() - player->exhaustItemAcquiredTime));

	return max(0, leftTime * 100 / EXHAUST_ITEM_DURATION);
}