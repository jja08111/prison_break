#ifndef __UPDATE_H__
#define __UPDATE_H__

#include "models.h"
#include "constants.h"
#include "utils.h"
#include "init.h"
#include "colors.h"
#include "render.h"

#include <conio.h>

// Ű �Է¿� ���� map�� ����Ͽ� position�� ������Ʈ�Ѵ�.
//
// Ű �Է� ������ ��ȯ�Ѵ�.
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
