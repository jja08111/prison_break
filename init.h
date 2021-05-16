#ifndef __INIT_H__
#define __INIT_H__

#include "map.h"
#include "stage.h"
#include "player.h"
#include "utils.h"

#include <time.h>

void initMap(Map* map, const Stage* const stage);
static void _initPlayer(Player* player, const Stage* const stage);
static void _initStage(Stage* stage);

void init(Stage* stage, Player* player, Map* map);

#endif