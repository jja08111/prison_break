#ifndef __INIT_H__
#define __INIT_H__

#include "models.h"
#include "utils.h"
#include "sounds.h"

#include <time.h>

void initMap(
	Map*				map,
	const Stage* const  stage
);

void init(
	Stage*			 stage,
	Player*			 player,
	MobHandler*		 mobHandler,
	Map*			 map,
	SoundController* soundController
);

#endif