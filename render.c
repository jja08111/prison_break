#include "render.h"

// 플레이어 시야 범위내에 (x,y)가 위치했으면 1을, 아니면 0을 반환한다.
static int _inVisionRange(
	int y, 
	int x,
	const Map* const	map,
	const Player* const	player
)
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

static int _ensureToBeWithinRange(
	const Map* const map,
	SMALL_RECT*		 rect
)
{
	// 한 칸도 겹치지 않는 경우
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

static void _drawMapCell(
	const Map* const map,
	COORD			 position
)
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

static void _drawMapCellAt(
	const Map* const map,
	COORD			 position
)
{
	gotoPosition(position);
	_drawMapCell(map, position);
}

static void _drawMapFromRect(
	const Map* const map,
	SMALL_RECT		 rect
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

static void _renderInitMap(
	const Map* const	map,
	const Player* const player
)
{
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	
	_drawDarknessFromRect(map, getRectOf(map));
	_drawMapFromRect(map, (SMALL_RECT) { 0, 0, visionRange, visionRange});
	_renderTargetSpace(map);
}

static void _renderMap(
	const Map* const	map,
	const Player* const player
)
{
	COORD prevPosition = player->prevPosition;
	COORD position = player->position;
	int visionRange = player->visionRange;

	SMALL_RECT playerVision = getPlayerVisionRect(player, map);
	// 현재 위치의 시야 한계 좌표값들이다.
	int top = playerVision.Top;
	int bottom = playerVision.Bottom;
	int left = playerVision.Left;
	int right = playerVision.Right;

	// 위로 이동한 경우
	if (position.Y < prevPosition.Y)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { left, bottom + 1, right, bottom + 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, right, top });
	}
	// 아래로 이동한 경우
	else if (position.Y > prevPosition.Y)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { left, top - 1, right, top - 1 });
		_drawMapFromRect(map, (SMALL_RECT) { left, bottom, right, bottom });
	}
	// 좌측으로 이동한 경우
	else if (position.X < prevPosition.X)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { right + 1, top, right + 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { left, top, left, bottom });
	}
	// 우측으로 이동한 경우
	else if (position.X > prevPosition.X)
	{
		_drawDarknessFromRect(map, (SMALL_RECT) { left - 1, top, left - 1, bottom });
		_drawMapFromRect(map, (SMALL_RECT) { right, top, right, bottom });
	}

	_renderTargetSpace(map);
}

static void _renderPlayer(const Player* const player)
{
	// 이전 위치와 다르면 지운다.
	if (!samePosition(player->position, player->prevPosition))
	{
		_drawEmptyIconAt(player->prevPosition);
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
		if (inRangeRect(position, getPlayerVisionRect(player, map)))
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

// 몹의 시야를 렌더링한다. 
//
// 이전과 방향이 바뀌었다면 이전 시야는 지운다.
static void _renderMobVision(
	const Mob* const	mob,
	const Player* const	player,
	const Map* const	map
) 
{
	COORD position = getMovedCoordInDirection(mob->position, mob->direction);
	
	textcolor(GREEN, MOB_VISION_COLOR);
	drawMobVisionInPlayerRange(position, mob->direction, map, player);

	// 이전 방향과 다르면 이전 시야를 지운다.
	if (mob->direction != mob->prevDirection)
	{
		COORD prevPosition = getMovedCoordInDirection(mob->prevPosition, mob->prevDirection);

		textcolor(SURFACE_COLOR, SURFACE_COLOR);
		drawMobVisionInPlayerRange(prevPosition, mob->prevDirection, map, player);
	}
}

// 몹과 몹의 시야를 렌더링한다.
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

	// 몹의 시야를 먼저 그려 몹이 지워지지 않도록 한다.
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

	// 몹을 그린다.
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

			if (inRangeRect(currentMob->prevPosition, playerVision) 
				&& *ptrCell != FLAG_MOB_VISION)
			{
				// 이전 위치는 지운다.
				_drawEmptyIconAt(prevPosition);
			}

			if (inRangeRect(position, playerVision))
			{
				gotoPosition(position);
				drawMobIcon(currentMob);
			}
		}
	}
}

// rect의 x값은 2칸을 한 칸으로 두어 계산한다.
static void _drawCenterAlignedText(
	SMALL_RECT	rect,
	const char* _Format,
	...
)
{
	char _Buffer[40];

	// _Buffer에 _ArgList을 포멧팅한다.
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

	y += 4;
	_drawCenterAlignedText(
		(SMALL_RECT) { map->width, y, CONSOLE_MAX_WIDTH / 2, y },
		"LIFE  : %d", player->life);
}

static void _renderDialogAtCenterMap(
	const Map* const map, 
	const char*		 _Format, 
	...
)
{
	SMALL_RECT boxRect = getRectOf(map);
	COORD centerPoint = getMapCenterPoint(map);
	int horizontalPadding = 12;
	char _Buffer[40];

	boxRect = (SMALL_RECT){
		centerPoint.X - horizontalPadding,
		centerPoint.Y - 1,
		centerPoint.X + horizontalPadding,
		centerPoint.Y + 1 };

	// _Buffer에 _ArgList을 포멧팅한다.
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vsprintf_l(_Buffer, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	textcolor(ON_DIALOG_COLOR, DIALOG_COLOR);

	_drawBox(boxRect);
	_drawCenterAlignedText(boxRect, _Buffer);
	Sleep(DIALOG_DURATION);
}

void renderSuccessDialog(const Map* const map)
{
	_renderDialogAtCenterMap(map, "성공! 다음 단계에 진입합니다.");
}

void renderFailDialog(const Map* const map)
{
	_renderDialogAtCenterMap(map, "교도관에게 적발되었습니다!");
}

void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
)
{
	_renderInterface(stage, player, map);
	
	// 초기 렌더링
	if (!map->hasInitRendered)
	{
		_renderInitMap(map, player);
		_renderPlayer(player);
		map->hasInitRendered = 1;
	}

	_renderMob(mobHandler, player, map);

	// 플레이어가 이동한 경우 렌더링
	if (!samePosition(player->position, player->prevPosition))
	{
		_renderMap(map, player);
		_renderPlayer(player);
	}
	// 플레이어가 방향을 바꾼 경우 플레이어 렌더링
	else if (player->direction != player->prevDirection)
	{
		_renderPlayer(player);
	}
}