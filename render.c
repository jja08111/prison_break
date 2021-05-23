#include "render.h"

static int _ensureToBeWithinRange(
	const Map* const map,
	SMALL_RECT*		 rect
)
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
			drawEmptyIconWithNoColor();
	}
}

static void _drawEmptyIconAt(COORD position)
{
	gotoPosition(position);
	drawEmptyIcon();
}

static void _drawDarknessFromRect(
	const Map* const map,
	SMALL_RECT		 rect
)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	textcolor(ON_SURFACE_COLOR, ON_SURFACE_COLOR);
	_drawBox(rect);
}

static void _drawMapCellWith(
	const Map* const map,
	COORD			 position,
	int				 backgroundColor
)
{
	switch (map->grid[position.Y][position.X]) {
	case FLAG_WALL: 
		drawWallIconWith(backgroundColor);
		break;
	case FLAG_TARGET: 
		drawTargetIcon();
		break;
	case FLAG_UNLIMIT_VISION_ITEM:
		drawUnlimitVisionItemIconWith(backgroundColor);
		break;
	default: 
		textcolor(backgroundColor, backgroundColor);
		drawEmptyIconWithNoColor();
	}
}

static void _drawMapCellAt(
	const Map* const map,
	COORD			 position
)
{
	gotoPosition(position);
	_drawMapCellWith(map, position, GREY);
}

static void _drawMapWith(
	const Map* const map,
	SMALL_RECT		 rect,
	int				 backgroundColor 
)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);

	int y, x;

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left, y);
		for (x = rect.Left;x <= rect.Right;++x)
			_drawMapCellWith(map, (COORD) { x, y }, backgroundColor);
	}	
}

void drawEntireMapWith(
	const Map* const map,
	int				 backgroundColor
)
{
	_drawMapWith(map, getMapRect(map), backgroundColor);
}

static void _renderTargetSpace(const Map* const map)
{
	COORD targetPosition = getTargetPosition(map);

	_drawMapWith(
		map,
		(SMALL_RECT) {
		targetPosition.X - TARGET_VISION_RANGE,
		targetPosition.Y - TARGET_VISION_RANGE,
		targetPosition.X + TARGET_VISION_RANGE,
		targetPosition.Y + TARGET_VISION_RANGE},
		DARK_GRAY);
}

void renderPlayer(
	const Player* const player,
	Map*			 	map
)
{
	SMALL_RECT willRemoveRange = getPlayerPreviousVisionRect(player, map);

	// ���� ��ġ�� �ٸ��� �����.
	if (!samePosition(player->position, player->prevPosition))
	{
		_drawEmptyIconAt(player->prevPosition);
	}

	if (hasPlayerVisionItem(player))
	{
		if (!map->hasDrawedEntireMap)
		{
			map->hasDrawedEntireMap = 1;
			_drawMapWith(map, getMapRect(map), GREY);
		}
	}
	else
	{
		// ������ �״���� ��� �÷��̾� ���� ��ġ�� ���ʸ� �����.
		if (player->direction == player->prevDirection)
		{
			switch (player->direction)
			{
			case DIRECTION_UP:
				willRemoveRange.Top = willRemoveRange.Bottom;
				break;
			case DIRECTION_DOWN:
				willRemoveRange.Bottom = willRemoveRange.Top;
				break;
			case DIRECTION_LEFT:
				willRemoveRange.Left = willRemoveRange.Right;
				break;
			case DIRECTION_RIGHT:
				willRemoveRange.Right = willRemoveRange.Left;
			}
		}
		// ���� �þߴ� �����.
		_drawMapWith(map, willRemoveRange, DARK_GRAY);
		// ���ο� �þߴ� �׸���.
		_drawMapWith(map, getPlayerVisionRect(player, map), GREY);
	}

	gotoPosition(player->position);
	drawPlayerIcon(player);
}

void drawMobVisionInPlayerRange(
	COORD				position,
	Direction			direction,
	const Map* const	map,
	const Player* const	player
)
{
	while (canPlace(position, map))
	{
		if (hasPlayerVisionItem(player)
			|| inRangeRect(position, getPlayerVisionRect(player, map)))
		{
			gotoPosition(position);
			drawEmptyIconWithNoColor();

			if (samePosition(position, player->position))
			{
				gotoPosition(position);
				drawPlayerIconWithNoColor(player);
			}
		}

		position = getMovedCoordInDirection(position, direction);
	}
}

// ���� �þ߸� �������Ѵ�. 
//
// ������ ������ �ٲ���ٸ� ���� �þߴ� �����.
static void _renderMobVision(
	const Mob* const	mob,
	const Player* const	player,
	const Map* const	map
) 
{
	COORD position = getMovedCoordInDirection(mob->position, mob->direction);
	
	textcolor(GREEN, MOB_VISION_COLOR);
	drawMobVisionInPlayerRange(position, mob->direction, map, player);

	// ���� ����� �ٸ��� ���� �þ߸� �����.
	if (mob->direction != mob->prevDirection)
	{
		COORD prevPosition = getMovedCoordInDirection(mob->prevPosition, mob->prevDirection);

		textcolor(SURFACE_COLOR, SURFACE_COLOR);
		drawMobVisionInPlayerRange(prevPosition, mob->prevDirection, map, player);
	}
}

// ���� ���� �þ߸� �������Ѵ�.
static void _renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
)
{
	COORD position, prevPosition;
	SMALL_RECT playerVision = getPlayerVisionRect(player, map);
	const Mob* currentMob;
	int i;

	// ���� �þ߸� ���� �׷� ���� �������� �ʵ��� �Ѵ�.
	for (i = 0;i < mobHandler->count;++i)
	{
		currentMob = &mobHandler->arrMob[i];

		if (currentMob->wasKilled)
			continue;

		position = currentMob->position;
		prevPosition = currentMob->prevPosition;

		if (!samePosition(prevPosition, position))
		{
			_renderMobVision(currentMob, player, map);
		}
	}

	// ���� �׸���.
	for (i = 0;i < mobHandler->count;++i)
	{
		currentMob = &mobHandler->arrMob[i];
		if (currentMob->wasKilled)
			continue;

		position = currentMob->position;
		prevPosition = currentMob->prevPosition;

		if (!samePosition(prevPosition, position))
		{
			int* ptrCell = getMapCellPtrFrom(currentMob->prevPosition, map);

			if (hasPlayerVisionItem(player) 
				|| (inRangeRect(currentMob->prevPosition, playerVision) 
				&& *ptrCell != FLAG_MOB_VISION))
			{
				// ���� ��ġ�� �����.
				_drawEmptyIconAt(prevPosition);
			}

			if (hasPlayerVisionItem(player)
				|| inRangeRect(position, playerVision))
			{
				gotoPosition(position);
				drawMobIcon(currentMob);
			}
		}
	}
}

// rect�� x���� 2ĭ�� �� ĭ���� �ξ� ����Ѵ�.
static void _drawCenterAlignedText(
	SMALL_RECT	rect,
	const char* _Format,
	...
)
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

static void _renderInterface(
	const Stage* const	stage,
	const Player* const player,
	const Map* const	map
)
{
	int y = 4;
	
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);

	_drawCenterAlignedText(
		(SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y }, 
		"SCORE : %d", stage->score);

	y += 4;
	_drawCenterAlignedText(
		(SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y },
		"LEVEL : %d", stage->level + 1);

	
}

static void _renderDialogAtCenterMap(
	const Map* const map, 
	const char*		 _Format, 
	...
)
{
	SMALL_RECT boxRect = getMapRect(map);
	COORD centerPoint = getMapCenterPoint(map);
	int horizontalPadding = 12;
	char _Buffer[40];

	boxRect = (SMALL_RECT){
		centerPoint.X - horizontalPadding,
		centerPoint.Y - 1,
		centerPoint.X + horizontalPadding,
		centerPoint.Y + 1 };

	// _Buffer�� _ArgList�� �������Ѵ�.
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vsprintf_l(_Buffer, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	textcolor(ON_DIALOG_COLOR, DIALOG_COLOR);

	_drawBox(boxRect);
	_drawCenterAlignedText(boxRect, _Buffer);
	Sleep(DIALOG_DURATION);
}

static void _renderSuccessDialog(const Map* const map)
{
	_renderDialogAtCenterMap(map, "����! ���� �ܰ迡 �����մϴ�.");
}

static void _renderFailDialog(const Map* const map)
{
	_renderDialogAtCenterMap(map, "���������� ���ߵǾ����ϴ�!");
}

void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
)
{
	_renderInterface(stage, player, map);
	
	// �ʱ� ������
	if (!map->hasInitRendered)
	{
		_drawDarknessFromRect(map, getMapRect(map));
		_renderTargetSpace(map);

		renderPlayer(player, map);
		map->hasInitRendered = 1;
	}

	_renderMob(mobHandler, player, map);

	// �÷��̾ �̵��� ��� ������
	if (!samePosition(player->position, player->prevPosition))
	{
		renderPlayer(player, map);
	}
	// �÷��̾ ������ �ٲ� ��� �÷��̾� ������
	else if (player->direction != player->prevDirection)
	{
		renderPlayer(player, map);
	}

	switch (player->state)
	{
	case STATE_CAUGHTED:
		_renderFailDialog(map);
		break;
	case STATE_SUCCESS:
		_renderSuccessDialog(map);
		break;
	default:
		break;
	}
}