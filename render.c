#include "render.h"
#include "big_number.h"
#include "gage_bar.h"
#include "record.h"

#include <string.h>

#define MAX_DIALOG_BUFFUER_SIZE 60

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
	goto2xyPosition(position);
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

	// 이전 위치와 다르면 지운다.
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
		// 방향이 그대로인 경우 플레이어 이전 위치인 뒤쪽만 지운다.
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
		// 이전 시야는 지운다.
		_drawMapWith(map, willRemoveRange, DARK_GRAY);
		// 새로운 시야는 그린다.
		_drawMapWith(map, getPlayerVisionRect(player, map), GRAY);
	}

	goto2xyPosition(screenPosition);
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
			goto2xyPosition(screenPosition);
			drawEmptyIconWithNoColor();

			if (samePosition(position, player->position))
			{
				goto2xyPosition(screenPosition);
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
	
	textcolor(PRIMARY_COLOR, SECONDARY_COLOR);
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
				// 이전 위치는 지운다.
				_drawEmptyIconAt(screenPrevPosition);
			}

			if (hasPlayerVisionItem(player)
				|| inRangeRect(position, playerVision))
			{
				goto2xyPosition(screenPosition);
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
	char _Buffer[MAX_DIALOG_BUFFUER_SIZE];

	// _Buffer에 _ArgList을 포멧팅한다.
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
	static int prevScore;
	static int prevKillingCount;
	static int prevTotalScore;
	static int prevStageLevel;
	int y;
	int visionItemPct;

	if (!map->hasInitRendered)
	{
		prevScore = -1;
		prevKillingCount = -1;
		prevTotalScore = -1;
		prevStageLevel = -1;
	}

	// 왼쪽 인터페이스 시작
	if (prevStageLevel != stage->level)
	{
		y = 5;
		drawBigNumberWithColor(stage->level + 1, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);
		y += 4;
		textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
		_drawTextAtLeft("단계", y);
	}

	if (prevScore != stage->score || prevStageLevel != stage->level)
	{
		y = 19;
		prevScore = stage->score;
		removeBigNumberWithColor((COORD) { LEFT_CENTER_X, y }, BACKGROUND_COLOR);
		drawBigNumberWithColor(stage->score, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);

		y += 4;
		textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
		_drawTextAtLeft("이번 단계 점수", y);
	}
	
	if (prevKillingCount != player->killingCount || prevStageLevel != stage->level)
	{
		y = 33;
		prevKillingCount = player->killingCount;
		removeBigNumberWithColor((COORD) { LEFT_CENTER_X, y }, BACKGROUND_COLOR);
		drawBigNumberWithColor(player->killingCount, (COORD) { LEFT_CENTER_X, y }, DARK_GRAY);

		y += 4;
		textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
		_drawTextAtLeft("교도관 제압", y);
	}
	// ~왼쪽 인터페이스 종료


	// 오른쪽 인터페이스 시작
	if (prevTotalScore != stage->totalScore || prevStageLevel != stage->level)
	{
		y = 5;
		prevTotalScore = stage->totalScore;
		removeBigNumberWithColor((COORD) { RIGHT_CENTER_X, y }, BACKGROUND_COLOR);
		drawBigNumberWithColor(stage->totalScore, (COORD) { RIGHT_CENTER_X, y }, ON_BACKGROUND_COLOR);
		y += 4;

		textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
		_drawTextAtRight("점수", y);
	}
	
	if (prevStageLevel != stage->level)
	{
		y = 31;
		goto2xy(RIGHT_INTERFACE_X + 2, y);
		textcolor(DARK_GRAY, BACKGROUND_COLOR);
		printf("─────────────");

		y = 33;
		textcolor(ON_BACKGROUND_COLOR, BACKGROUND_COLOR);
		_drawTextAtRight("♣ 시야 아이템", y);
	}
	
	visionItemPct = getVisionItemLeftTimePercent(player);
	y = 34;
	drawGageBar(
		visionItemPct,
		(COORD) {
		RIGHT_CENTER_X, y
	},
		visionItemPct != 0
			? GREEN
			: DARK_GRAY);
	// ~오른쪽 인터페이스 종료

	prevStageLevel = stage->level;
}

#define DIALOG_WIDTH 30

static void _renderDialogAtCenter(
	const Map* const map, 
	const char*		 _Format, 
	...
)
{
	SMALL_RECT boxRect = getMapScreenRect(map);
	COORD centerPoint = getMapScreenCenterPoint(map);
	int halfWidth = map->width/2;
	char _Buffer[MAX_DIALOG_BUFFUER_SIZE];

	boxRect = (SMALL_RECT){
		centerPoint.X - DIALOG_WIDTH/2,
		centerPoint.Y - 1,
		centerPoint.X + DIALOG_WIDTH/2,
		centerPoint.Y + 1 };

	// _Buffer에 _ArgList을 포멧팅한다.
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
	_renderDialogAtCenter(map, "성공! 다음 단계에 진입합니다.");
}

static void _renderFailDialog(const Map* const map)
{
	_renderDialogAtCenter(map, "교도관에게 적발되었습니다!");
}

void renderScoreInputDialog(
	const Map* const	map,
	const Stage* const	stage,
	const Player* const player
)
{
	Record record;
	COORD cusorPosition = getMapCenterCoord(map);
	char name[MAX_NAME_LENGTH];

	_renderDialogAtCenter(map, "점수는 %d점 입니다! 저장할 닉네임을 입력하세요.", stage->totalScore);
	showCursor();

	while (1)
	{
		fgets(name, MAX_NAME_LENGTH, stdin);
		// 개행 문자 제거
		name[strlen(name) - 1] = '\0';

		if (hasSpace(name, MAX_NAME_LENGTH))
		{

			continue;
		}
		else
		{
			strcpy(record.name, name);
			record.killingCount = player->killingCount;
			record.reachedStageLevel = stage->level;
			record.totalScore = stage->totalScore;

			if (writeRecordFile(&record))
				return;

			Sleep(500);
			break;
		}
	}
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
		_drawInGameBackgroundBox();

		_drawDarknessFromRect(map, getMapRect(map));
		_renderTargetSpace(map);

		renderPlayer(player, map);
		map->hasInitRendered = 1;
	}

	// 플레이어가 이동한 경우, 방향을 바꾼 경우 플레이어 렌더링
	if (!samePosition(player->position, player->prevPosition) || 
		(player->direction != player->prevDirection))
	{
		renderPlayer(player, map);
	}
	// 몹을 나중에 렌더링해야 플레이어가 몹에게 잡혔을때 깔끔하게 처리됨
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