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

static void _drawBox(SMALL_RECT rect)
{
	int y, x;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left, y);
		for (x = rect.Left;x <= rect.Right;++x)
			printf(ICON_EMPTY);
	}
}

static void _drawEmptyIconAt(COORD position)
{
	gotoPosition(position);
	drawEmptyIcon();
}

static void _drawDarknessFromRect(const Map* const map, SMALL_RECT rect)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	textcolor(ON_SURFACE_COLOR, ON_SURFACE_COLOR);
	_drawBox(rect);
}

static void _drawMapCell(const Map* const map, COORD position)
{
	switch (map->grid[position.Y][position.X]) {
	case FLAG_WALL: 
		drawWallIcon();
		break;
	case FLAG_TARGET: 
		drawTargetIcon();
		break;
	default: 
		drawEmptyIcon();
	}
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

static void _renderTargetSpace(const Map* const map)
{
	COORD targetPosition = getTargetPosition(map);

	_drawMapFromRect(map,
		(SMALL_RECT) {
		targetPosition.X - TARGET_VISION_RANGE,
		targetPosition.Y - TARGET_VISION_RANGE,
		targetPosition.X + TARGET_VISION_RANGE,
		targetPosition.Y + TARGET_VISION_RANGE});
}

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	
	_drawDarknessFromRect(map, getMapRect(map));
	_drawMapFromRect(map, (SMALL_RECT) { 0, 0, visionRange, visionRange});
	_renderTargetSpace(map);
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
		_drawDarknessFromRect(map, (SMALL_RECT) { left, bottom + 1, right, bottom + 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, right, top });
	}
	// �Ʒ��� �̵��� ���
	else if (position.Y > prevPosition.Y)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { left, top - 1, right, top - 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, bottom, right, bottom });
	}
	// �������� �̵��� ���
	else if (position.X < prevPosition.X)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { right + 1, top, right + 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, left, bottom });
	}
	// �������� �̵��� ���
	else if (position.X > prevPosition.X)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { left - 1, top, left - 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { right, top, right, bottom });
	}

	_renderTargetSpace(map);
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

// rect�� x���� 2ĭ�� �� ĭ���� �ξ� ����Ѵ�.
static void _drawCenterAlignedText(SMALL_RECT rect, const char* _Format, ...)
{
	char _Buffer[40];

	// _Buffer�� _ArgList�� �������Ѵ�.
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vsprintf_l(_Buffer, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	gotoCenterForAlignString(rect, _Buffer);
	printf(_Buffer);
}

static void _renderInterface(const Stage* const stage, const Player* const player, const Map* const map)
{
	int y = 4;
	
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);

	_drawCenterAlignedText((SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y }, "SCORE : %d", stage->score);

	y += 4;
	_drawCenterAlignedText((SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y }, "LEVEL : %d", stage->level + 1);

	y += 4;
	_drawCenterAlignedText((SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y }, "LIFE  : %d", player->life);
}

static void _renderDialogAtCenterMap(const Map* const map, const char* _Format, ...)
{
	SMALL_RECT boxRect = getMapRect(map);
	COORD centerPoint = getMapCenterPoint(map);
	int horizontalPadding = 8;
	char _Buffer[40];

	boxRect = (SMALL_RECT){
		boxRect.Left + horizontalPadding,
		centerPoint.Y - 1,
		boxRect.Right - horizontalPadding,
		centerPoint.Y + 1 };

	// _Buffer�� _ArgList�� �������Ѵ�.
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vsprintf_l(_Buffer, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	textcolor(ON_DIALOG_COLOR, DIALOG_COLOR);

	_drawBox(boxRect);
	_drawCenterAlignedText(boxRect, _Buffer);
}

static void _renderSuccessDialog(const Map* const map, const Stage* const stage)
{
	_renderDialogAtCenterMap(map, "Successed the %d level!", stage->level + 1);
}

void render(const Stage* const stage, const Player* const player, Map* map)
{
	// ��ǥ�� ������ ���
	if (onReachedTargetPoint(player, map))
	{
		_renderSuccessDialog(map, stage);
	}
	
	// �ʱ� ������
	if (!map->hasInitRendered)
	{
		_renderInitMap(map, player);
		_renderPlayer(player);
		map->hasInitRendered = 1;
	}

	_renderInterface(stage, player, map);

	// �÷��̾ �̵��� ��� ������
	if (!samePosition(player->position, player->prevPosition))
	{
		

		_renderMap(map, player);
		_renderPlayer(player);
	}
}