#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"

#include <assert.h>
#include <string.h>

static int _inVisionRange(int y, int x, const Map* const map, const Player* const player);

// 사각형이 범위에 있지 않으면 범위에 들도록 수정한다.
//
// 만약 범위가 map에 한 칸도 겹치지 않으면 0을 반환한다.
static int _ensureToBeWithinRange(const Map* const map, SMALL_RECT* rect);

static void _drawBox(SMALL_RECT rect);



static void _drawEmptyIconAt(COORD position);

// 빈 공간을 사각형 모양으로 그린다.
static void _drawDarknessFromRect(const Map* const map, SMALL_RECT rect);



// map[y][x]를 그린다.
static void _drawMapCell(const Map* const map, COORD position);

// map[y][x]를 position 위치에 한 칸 그린다.
static void _drawMapCellAt(const Map* const map, COORD position);

// 직사각형 범위만 맵을 그린다.
//
// topLeft는 좌측 상단이어야만 하고 bottomRight는 우측 하단이어야만 한다.
static void _drawMapFromRect(const Map* const map, SMALL_RECT rect);



// 도착지점을 렌더링한다.
static void _renderTargetSpace(const Map* const map);



// 초기 맵을 플레이어 시야에 맞춰 그린다. 
//
// 도착 지점은 맵의 우측 하단이다.
static void _renderInitMap(const Map* const map, const Player* const player);

// 플레이어가 이동한 방향의 맵을 그리며, 이전 방향 부분의 맵은 지운다.
static void _renderMap(const Map* const map, const Player* const player);

// 플레이어를 그린다. 만약 이전 위치와 현재 위치가 다르다면 지우고 새로 그린다.
static void _renderPlayer(const Player* const player);



static void _drawCenterAlignedText(SMALL_RECT rect, const char* _Format, ...);

static void _renderInterface(const Stage* const stage, const Player* const player, const Map* const map);

static void _renderDialogAtCenterMap(const Map* const map, const char* _Format, ...);

static void _renderSuccessDialog(const Map* const map, const Stage* const stage);



void render(const Stage* const stage, const Player* const player, Map* map);

#endif