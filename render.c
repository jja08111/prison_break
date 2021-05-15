#include "render.h"

// 플레이어 시야 범위내에 (x,y)가 위치했으면 1을, 아니면 0을 반환한다.
static int _inVisionRange(int y, int x, const Map* const map, const Player* const player)
{
	int visionRange = player->visionRange;
	int py = player->position.Y;
	int px = player->position.X;

	int minY = max(0, py - visionRange);
	int minX = max(0, px - visionRange);
	int maxY = min(map->height, py + visionRange);
	int maxX = min(map->width, px + visionRange);
	
	return minY <= y && y <= maxY && minX <= x && x <= maxX;
}

static int rangedNum(int num, int minNum, int maxNum)
{
	return max(minNum, min(num, maxNum));
}

static int _ensureToBeWithinRange(const Map* const map, COORD* topLeft, COORD* bottomRight)
{
	// 한 칸도 겹치지 않는 경우
	if (bottomRight->Y < 0 || bottomRight->X < 0 
		|| topLeft->Y > map->height || topLeft->X > map->width)
		return 0;

	topLeft->Y = rangedNum(topLeft->Y, 0, map->height);
	topLeft->X = rangedNum(topLeft->X, 0, map->width);
	bottomRight->Y = rangedNum(bottomRight->Y, 0, map->height);
	bottomRight->X = rangedNum(bottomRight->X, 0, map->width);
	return 1;
}

static void _drawEmptyIconAt(COORD position)
{
	gotoPosition(position);
	printEmptyIcon();
}

static void _drawEmptyIconFromRect(const Map* const map, COORD topLeft, COORD bottomRight)
{
	assert(topLeft.X <= bottomRight.X && topLeft.Y <= bottomRight.Y);
	int y, x;

	if (!_ensureToBeWithinRange(map, &topLeft, &bottomRight))
		return;

	for (y = topLeft.Y;y <= bottomRight.Y;++y)
	{
		goto2xy(topLeft.X, y);
		for (x = topLeft.X;x <= bottomRight.X;++x)
			printEmptyIcon();
	}
}

static void _drawMapCell(const Map* const map, COORD position)
{
	map->grid[position.Y][position.X] == FLAG_WALL
		? printWallIcon()
		: printEmptyIcon();
}

static void _drawMapCellAt(const Map* const map, COORD position)
{
	gotoPosition(position);
	_drawMapCell(map, position);
}

static void _drawMapFromRect(const Map* const map, COORD topLeft, COORD bottomRight)
{
	assert(topLeft.X <= bottomRight.X && topLeft.Y <= bottomRight.Y);
	int y, x;

	if (!_ensureToBeWithinRange(map, &topLeft, &bottomRight))
		return;

	for (y = topLeft.Y;y <= bottomRight.Y;++y)
	{
		goto2xy(topLeft.X, y);
		for (x = topLeft.X;x <= bottomRight.X;++x)
			_drawMapCell(map, (COORD) { x, y });
	}	
}

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	
	_drawEmptyIconFromRect(map, (COORD) { 0, 0 }, (COORD) { map->width, map->height});
	_drawMapFromRect(map, (COORD) { 0, 0 }, (COORD) { visionRange, visionRange});
}

static void _renderMap(const Map* const map, const Player* const player)
{
	COORD prevPosition = player->prevPosition;
	COORD position = player->position;
	int visionRange = player->visionRange;

	// 현재 위치의 시야 한계 좌표값들이다.
	int top = position.Y - visionRange;
	int bottom = position.Y + visionRange;
	int left = position.X - visionRange;
	int right = position.X + visionRange;

	// 위로 이동한 경우
	if (position.Y < prevPosition.Y)
	{
		_drawEmptyIconFromRect(map, (COORD) { left, bottom + 1 }, (COORD) { right, bottom + 1 });
		_drawMapFromRect(map, (COORD) { left, top }, (COORD) { right, top });
	}
	// 아래로 이동한 경우
	else if (position.Y > prevPosition.Y)
	{
		_drawEmptyIconFromRect(map, (COORD) { left, top - 1 }, (COORD) { right, top - 1 });
		_drawMapFromRect(map, (COORD) { left, bottom }, (COORD) { right, bottom });
	}
	// 좌측으로 이동한 경우
	else if (position.X < prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (COORD) { right + 1, top }, (COORD) { right + 1, bottom });
		_drawMapFromRect(map, (COORD) { left, top }, (COORD) { left, bottom });
	}
	// 우측으로 이동한 경우
	else if (position.X > prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (COORD) { left - 1, top }, (COORD) { left - 1, bottom });
		_drawMapFromRect(map, (COORD) { right, top }, (COORD) { right, bottom });
	}
}

static void _renderPlayer(const Player* const player)
{
	// 이전 위치와 다르면 지운다.
	if (!samePosition(player->position, player->prevPosition))
	{
		_drawEmptyIconAt(player->prevPosition);
	}

	gotoPosition(player->position);
	printPlayerIcon();
}

static void _renderInterface(const Stage* const stage, const Player* const player)
{
	//goto2xy
}

void render(const Stage* const stage, const Player* const player, Map* map)
{
	if (!map->hasInitRendered)
	{
		_renderInitMap(map, player);
		_renderPlayer(player);
		map->hasInitRendered = 1;
	}

	// 플레이어가 이동한 경우 렌더링
	if (!samePosition(player->position, player->prevPosition))
	{
		_renderMap(map, player);
		_renderPlayer(player);
	}
}