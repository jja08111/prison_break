#ifndef __UPDATE_H__
#define __UPDATE_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "constants.h"

void updatePlayerPosition(Player* player, const Map* const map, unsigned char keybdInput);

static void _levelUpStage(Stage* stage);

void update(Stage* stage, Player* player, Map* map);

#endif
