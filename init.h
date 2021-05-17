#ifndef __INIT_H__
#define __INIT_H__

#include "models.h"
#include "utils.h"

#include <time.h>

void initMap(
	Map*				map,
	const Stage* const  stage
);

static void _initPlayer(
	Player*				player,
	const Stage* const	stage
);

static void _initStage(Stage* stage);

static void _initMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Map* const	map
);

void init(
	Stage*		stage,
	Player*		player,
	MobHandler* mobHandler,
	Map*		map
);

#endif