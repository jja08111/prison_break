#include "render.h"
#include "big_number.h"
#include "gage_bar.h"

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

static void drawBox(SMALL_RECT rect)
{
	int y, x;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left, y);
		for (x = rect.Left;x <= rect.Right;++x)
			drawEmptyIconWithNoColor();
	}
}

static void _drawInGameBackgroundBox()
{
	textcolor(DARK_GRAY, DARK_GRAY);
	drawBox((SMALL_RECT) { INTERFACE_WIDTH, 0, SCREEN_WIDTH/2 - INTERFACE_WIDTH-1, SCREEN_HEIGHT-1 });
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

	int pivotY = map->topLeftPosition.Y;
	int pivotX = map->topLeftPosition.X;

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	textcolor(ON_SURFACE_COLOR, ON_SURFACE_COLOR);
	drawBox((SMALL_RECT) {
		rect.Left + pivotX,
		rect.Top + pivotY,
		rect.Right + pivotX,
		rect.Bottom + pivotY
	});
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
		drawVisionItemIconWith(backgroundColor);
		break;
	default: 
		textcolor(backgroundColor, backgroundColor);
		drawEmptyIconWithNoColor();
	}
}

static void _drawMapWith(
	const Map* const map,
	SMALL_RECT		 rect,
	int				 backgroundColor 
)
{
	assert(rect.Top <= rect.Bottom && rect.Left <= rect.Right);

	COORD topLeft = map->topLeftPosition;
	int y, x;

	if (!_ensureToBeWithinRange(map, &rect))
		return;

	for (y = rect.Top;y <= rect.Bottom;++y)
	{
		goto2xy(rect.Left + topLeft.X, y + topLeft.Y);
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

	COORD screenPosition = getScreenPostion(player->position, map);
	COORD screenPrevPosition = getScreenPostion(player->prevPosition, map);

	// ���� ��ġ�� �ٸ��� �����.
	if (!samePosition(player->position, player->prevPosition))
	{
		_drawEmptyIconAt(screenPrevPosition);
	}

	if (hasPlayerVisionItem(player))
	{
		if (!map->hasDrawedEntireMap)
		{
			map->hasDrawedEntireMap = 1;
			_drawMapWith(map, getMapRect(map), GRAY);
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
		_drawMapWith(map, getPlayerVisionRect(player, map), GRAY);
	}

	gotoPosition(screenPosition);
	drawPlayerIcon(player);
}

void drawMobVisionInPlayerRange(
	COORD				position,
	Direction			direction,
	const Map* const	map,
	const Player* const	player
)
{
	COORD screenPosition;

	while (canPlace(position, map))
	{
		screenPosition = getScreenPostion(position, map);

		if (hasPlayerVisionItem(player)
			|| inRangeRect(position, getPlayerVisionRect(player, map)))
		{
			gotoPosition(screenPosition);
			drawEmptyIconWithNoColor();

			if (samePosition(position, player->position))
			{
				gotoPosition(screenPosition);
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
	
	textcolor(PRIMARY_COLOR, SECONDARY_COLOR);
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
void renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
)
{
	COORD position, prevPosition;
	COORD screenPosition, screenPrevPosition;
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

		screenPosition = getScreenPostion(position, map);
		screenPrevPosition = getScreenPostion(prevPosition, map);

		if (!samePosition(prevPosition, position))
		{
			int* ptrPreviousCell = getMapCellPtrFrom(prevPosition, map);

			if ((hasPlayerVisionItem(player) || inRangeRect(currentMob->prevPosition, playerVision))
				&& *ptrPreviousCell != FLAG_MOB_VISION
				&& !samePosition(prevPosition,player->position)
				)
			{
				// ���� ��ġ�� �����.
				_drawEmptyIconAt(screenPrevPosition);
			}

			if (hasPlayerVisionItem(player)
				|| inRangeRect(position, playerVision))
			{
				gotoPosition(screenPosition);
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


#define RIGHT_INTERFACE_X (SCREEN_WIDTH/2 - INTERFACE_WIDTH)

#define LEFT_CENTER_X	(INTERFACE_WIDTH / 2)
#define RIGHT_CENTER_X	((SCREEN_WIDTH / 2 + RIGHT_INTERFACE_X) / 2)

static void _drawTextAtLeft(const char* _Format, int y)
{
	_drawCenterAlignedText((SMALL_RECT) { 0, y, INTERFACE_WIDTH, y }, _Format);
}

static void _drawTextAtRight(const char* _Format, int y)
{
	_drawCenterAlignedText((SMALL_RECT) { RIGHT_INTERFACE_X, y, SCREEN_WIDTH / 2, y }, _Format);
}

static void _renderInterface(
	const Stage* const	stage,
	const Player* const player,
	const Map* const	map
)
{
	static int prevScore = 0;
	static int prevKillCount = 0;
	static int prevTotalScore = 0;
	int y = 5;
	int visionItemPct;

	// ���� �������̽� ����
	drawBigNumberWithColor(stage->level + 1, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);
	y += 4;
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtLeft("�ܰ�", y);


	y += 10;
	if (prevScore != stage->score)
	{
		prevScore = stage->score;
		removeBigNumberWithColor((COORD) { LEFT_CENTER_X, y }, BACKGROUND_COLOR);
	}
	drawBigNumberWithColor(stage->score, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);
	y += 4;
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtLeft("�̹� �ܰ� ����", y);

	y += 10;
	if (prevKillCount != player->killCount)
	{
		prevKillCount = player->killCount;
		removeBigNumberWithColor((COORD) { LEFT_CENTER_X, y }, BACKGROUND_COLOR);
	}
	drawBigNumberWithColor(player->killCount, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);
	y += 4;
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtLeft("������ ����", y);
	// ~���� �������̽� ����


	// ������ �������̽� ����
	y = 5;
	if (prevScore != stage->totalScore)
	{
		prevScore = stage->totalScore;
		removeBigNumberWithColor((COORD) { RIGHT_CENTER_X, y }, BACKGROUND_COLOR);
	}
	drawBigNumberWithColor(stage->totalScore, (COORD) { RIGHT_CENTER_X, y }, ON_BACKGROUND_COLOR);
	y += 4;
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtRight("����", y);

	y = 31;
	
	goto2xy(RIGHT_INTERFACE_X + 2, y);
	textcolor(DARK_GRAY, BACKGROUND_COLOR);
	printf("��������������������������");

	y += 2;
	visionItemPct = getVisionItemLeftTimePercent(player);
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtRight("�� �þ� ������", y);
	y++;
	drawGageBar(
		visionItemPct,
		(COORD) {
		RIGHT_CENTER_X, y
	},
		visionItemPct != 0
			? GREEN
			: DARK_GRAY);

	y += 3;
	textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
	_drawTextAtRight("�� �þ� ������", y);
	y++;
	drawGageBar(
		visionItemPct,
		(COORD) { RIGHT_CENTER_X, y },
		visionItemPct != 0 
			? GREEN 
			: DARK_GRAY);
	
}

static void _renderDialogAtMapCenter(
	const Map* const map, 
	const char*		 _Format, 
	...
)
{
	SMALL_RECT boxRect = getMapScreenRect(map);
	COORD centerPoint = getMapScreenCenterPoint(map);
	int halfWidth = map->width/2;
	char _Buffer[40];

	boxRect = (SMALL_RECT){
		centerPoint.X - halfWidth + 2,
		centerPoint.Y - 1,
		centerPoint.X + halfWidth - 2,
		centerPoint.Y + 1 };

	// _Buffer�� _ArgList�� �������Ѵ�.
	va_list _ArgList;
	__crt_va_start(_ArgList, _Format);
	_vsprintf_l(_Buffer, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	textcolor(ON_DIALOG_COLOR, DIALOG_COLOR);

	drawBox(boxRect);
	_drawCenterAlignedText(boxRect, _Buffer);
	Sleep(DIALOG_DURATION);
}

static void _renderSuccessDialog(const Map* const map)
{
	_renderDialogAtMapCenter(map, "����! ���� �ܰ迡 �����մϴ�.");
}

static void _renderFailDialog(const Map* const map)
{
	_renderDialogAtMapCenter(map, "���������� ���ߵǾ����ϴ�!");
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
		_drawInGameBackgroundBox();

		_drawDarknessFromRect(map, getMapRect(map));
		_renderTargetSpace(map);

		renderPlayer(player, map);
		map->hasInitRendered = 1;
	}

	// �÷��̾ �̵��� ���, ������ �ٲ� ��� �÷��̾� ������
	if (!samePosition(player->position, player->prevPosition) || 
		(player->direction != player->prevDirection))
	{
		renderPlayer(player, map);
	}
	// ���� ���߿� �������ؾ� �÷��̾ ������ �������� ����ϰ� ó����
	renderMob(mobHandler, player, map);

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