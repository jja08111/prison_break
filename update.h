#ifndef __UPDATE_H__
#define __UPDATE_H__

#include "models.h"
#include "constants.h"
#include "utils.h"
#include "init.h"
#include "colors.h"
#include "render.h"

#include <conio.h>

// 키 입력에 따라 map을 고려하여 position을 업데이트한다.
//
// 키 입력 방향을 반환한다.
Direction updatePositionByInput(
	COORD*				position,
	const Map* const	map,
	unsigned char		keybdInput
);

static void _setNextStage(
	Stage*	stage, 
	Player*	player, 
	Map*	map
);


static void _updateStage(
	Stage*	stage,
	Player* player,
	COORD*	newPosition,
	Map*	map
);

static void _updatePlayer(
	Player*		player,
	COORD*		newPosition,
	Direction*	newDirection,
	Map*		map
);

static void _updateMobPosition(
	Mob*				mob,
	const Player* const player,
	const Map* const	map
);

static void _updateMobVisionFlagToMap(
	const Mob* const mob,
	const Map* const map
);

static void _updateMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Map* const	map
);

void update(
	Stage*		stage,
	Player*		player,
	MobHandler* mobHandler,
	Map*		map,
	COORD*		newPlayerPosition,
	Direction*	newDirection
);

#endif
