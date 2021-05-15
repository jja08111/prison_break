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

static int _ensureToBeWithinRange(const Map* const map, SMALL_RECT* rect)
{
	// �� ĭ�� ��ġ�� �ʴ� ���
	if (rect->Bottom < 0 || rect->Right < 0
		|| rect->Top > map->height || rect->Left > map->width)
		return 0;

	rect->Bottom = rangedNum(rect->Bottom, 0, map->height);
	rect->Top = rangedNum(rect->Top, 0, map->height);
	rect->Left = rangedNum(rect->Left, 0, map->width);
	rect->Right = rangedNum(rect->Right, 0, map->width);
	return 1;
}

static void _drawEmptyIconAt(COORD position)
{
	gotoPosition(position);
	drawEmptyIcon();
}

static void _drawEmptyIconFromRect(const Map* const map, SMALL_RECT rect)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);
	int y, x;

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left, y);
		for (x = rect.Left;x <= rect.Right;++x)
			drawEmptyIcon();
	}
}

static void _drawMapCell(const Map* const map, COORD position)
{
	map->grid[position.Y][position.X] == FLAG_WALL
		? drawWallIcon()
		: drawEmptyIcon();
}

static void _drawMapCellAt(const Map* const map, COORD position)
{
	gotoPosition(position);
	_drawMapCell(map, position);
}

static void _drawMapFromRect(const Map* const map, SMALL_RECT rect)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);
	int y, x;

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left, y);
		for (x = rect.Left;x <= rect.Right;++x)
			_drawMapCell(map, (COORD) { x, y });
	}	
}

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	
	_drawEmptyIconFromRect(map, (SMALL_RECT) { 0, 0, map->width, map->height});
	_drawMapFromRect(map, (SMALL_RECT) { 0, 0, visionRange, visionRange});
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
		_drawEmptyIconFromRect(map, (SMALL_RECT) { left, bottom + 1, right, bottom + 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, right, top });
	}
	// �Ʒ��� �̵��� ���
	else if (position.Y > prevPosition.Y)
	{
		_drawEmptyIconFromRect(map, (SMALL_RECT) { left, top - 1, right, top - 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, bottom, right, bottom });
	}
	// �������� �̵��� ���
	else if (position.X < prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (SMALL_RECT) { right + 1, top, right + 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, left, bottom });
	}
	// �������� �̵��� ���
	else if (position.X > prevPosition.X)
	{
		_drawEmptyIconFromRect(map, (SMALL_RECT) { left - 1, top, left - 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { right, top, right, bottom });
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
	drawPlayerIcon();
}

static void _drawCenterAlignedText(const char* str, SMALL_RECT rect)
{

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