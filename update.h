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

void updateMobPosition(
	Mob* mob,
	Map* map
);

void update(
	Stage*			 stage,
	Player*			 player,
	MobHandler*		 mobHandler,
	Map*			 map,
	SoundController* soundController,
	COORD*			 newPlayerPosition,
	Direction*		 newDirection
);

#endif
