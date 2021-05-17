#ifndef __UPDATE_H__
#define __UPDATE_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "constants.h"
#include "utils.h"
#include "init.h"
#include "colors.h"

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

static void _handleStageSuccess(
	Stage*	stage,
	Player* player,
	Map*	map,
	COORD*	newPosition
);

static void _updatePlayer(
	Player*		player,
	COORD*		newPosition,
	Direction*	newDirection
);

void update(
	Stage*		stage,
	Player*		player,
	Map*		map,
	COORD*		newPlayerPosition,
	Direction*	newDirection
);

#endif
