#ifndef __UPDATE_H__
#define __UPDATE_H__

#include "map.h"
#include "player.h"
#include "stage.h"
#include "constants.h"
#include "utils.h"

void updatePosition(COORD* position, const Map* const map, unsigned char keybdInput);

static void _levelUpStage(Stage* stage);

void update(Stage* stage, Player* player, Map* map, COORD updatedPosition);

#endif
