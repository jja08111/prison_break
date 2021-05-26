#ifndef __RENDER_H__
#define __RENDER_H__

#include "models.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"
#include "sounds.h"

#include <assert.h>
#include <string.h>

// 사각형이 범위에 있지 않으면 범위에 들도록 수정한다.
//
// 만약 범위가 map에 한 칸도 겹치지 않으면 0을 반환한다.
static int _ensureToBeWithinRange(
	const Map* const map, 
	SMALL_RECT*		 rect
);



static void drawBox(SMALL_RECT rect);

static void _drawEmptyIconAt(COORD position);

// 빈 공간을 사각형 모양으로 그린다.
static void _drawDarknessFromRect(
	const Map* const map,
	SMALL_RECT		 rect
);



// map[y][x]를 그린다.
static void _drawMapCellWith(
	const Map* const map,
	COORD			 position,
	int				 emptyCellColor
);

// 직사각형 범위만 맵을 그린다.
//
// topLeft는 좌측 상단이어야만 하고 bottomRight는 우측 하단이어야만 한다.
static void _drawMapWith(
	const Map* const map,
	SMALL_RECT		 rect,
	int				 emptyCellColor
);

void drawEntireMapWith(
	const Map* const map,
	int				 backgroundColor
);

// 도착지점을 렌더링한다.
static void _renderTargetSpace(const Map* const map);

// 플레이어와 플레이어 시야를 그린다.
// 
// 만약 이전 위치와 현재 위치가 다르다면 지우고 새로 그린다.
void renderPlayer(
	const Player* const player,
	Map*				map
);

// 몹의 시야를 렌더링한다.
//
// position 위치부터 맵의 벽에 닿을 때까지 렌더링한다. 해당 위치에
// 플레이어가 위치했다면 플레이어 아래에 그린다.
void drawMobVisionInPlayerRange(
	COORD				initPosition,
	Direction			direction,
	const Map* const 	map,
	const Player* const	player
);

static void _renderMobVision(
	const Mob* const	mob,
	const Player* const	player,
	const Map* const	map
);

void renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
);



static void _drawCenterAlignedText(
	SMALL_RECT	rect, 
	const char* _Format, 
	...
);

static void _renderInterface(
	const Stage* const	stage, 
	const Player* const player,
	const Map* const	map
);

static void _renderDialogAtMapCenter(
	const Map* const map,
	const char*		 _Format,
	...
);

static void _renderSuccessDialog(const Map* const map);

static void _renderFailDialog(const Map* const map);



void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
);

#endif