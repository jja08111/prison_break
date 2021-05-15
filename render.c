#include "render.h"

// �÷��̾� �þ� �������� (x,y)�� ��ġ������ 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
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
	// �� ĭ�� ��ġ�� �ʴ� ���
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

	// ���� ��ġ�� �þ� �Ѱ� ��ǥ�����̴�.
	int top = position.Y - visionRange;
	int bottom = position.Y + visionRange;
	int left = position.X - visionRange;
	int right = position.X + visionRange;

	// ���� �̵��� ���
	if (position.Y < prevPosition.Y)
	{
		_drawEmptyIconFromRect(map, (COORD) { left, bottom + 1 }, (COORD) { right, bottom + 1 });
		_drawMapFromRect(map, (COORD) { left, top }, (COORD) { right, top });
	}
	// �Ʒ��� �̵��� ���
	else if (position.Y > prevPosition.Y)
	{
		_drawEmptyIconFromRect(map, (COORD) { left, top - 1 }, (COORD) { right, top - 1 });
		_drawMapFromRect(map, (COORD) { left, bottom }, (COORD) { right, bottom });
	}
	// �������� �̵��� ���
	else if (position.X < prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (COORD) { right + 1, top }, (COORD) { right + 1, bottom });
		_drawMapFromRect(map, (COORD) { left, top }, (COORD) { left, bottom });
	}
	// �������� �̵��� ���
	else if (position.X > prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (COORD) { left - 1, top }, (COORD) { left - 1, bottom });
		_drawMapFromRect(map, (COORD) { right, top }, (COORD) { right, bottom });
	}
}

static void _renderPlayer(const Player* const player)
{
	// ���� ��ġ�� �ٸ��� �����.
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

	// �÷��̾ �̵��� ��� ������
	if (!samePosition(player->position, player->prevPosition))
	{
		_renderMap(map, player);
		_renderPlayer(player);
	}
}