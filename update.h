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
