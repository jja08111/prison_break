#ifndef __RENDER_H__
#define __RENDER_H__

#include "models.h"
#include "utils.h"
#include "icons.h"
#include "constants.h"
#include "sounds.h"

#include <assert.h>
#include <string.h>

void drawEntireMapWith(
	const Map* const map,
	int				 backgroundColor
);

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

void renderMob(
	const MobHandler* const mobHandler,
	const Player* const		player,
	const Map* const		map
);

void render(
	const Stage* const		stage,
	const Player* const		player,
	const MobHandler* const mobHandler,
	Map*					map
);

#endif