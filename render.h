#ifndef __RENDER_H__
#define __RENDER_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "utils.h"
#include "icons.h"

// 초기 맵을 플레이어 시야에 맞춰 그린다. 
static void _renderInitMap(const Map* const map, const Player* const player);

static void _renderMap(const Map* const map, const Player* const player, COORD prevPosition);

// 플레이어를 그리는데 이전 위치와 현재 위치가 다르면 지우고 새로 그린다.
static void _renderPlayer(const Player* const player, COORD prevPosition);

void render(const Stage* const stage, const Player* const player, const Map* const map);

#endif