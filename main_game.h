#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "ui.h"
#include "map.h"
#include "player.h"
#include "utils.h"
#include "constants.h"

#include <conio.h>
#include <time.h>
#include <stdlib.h>

void init(Stage* stage, Player* player, Map* map);

// �̷� ������ �����Ѵ�.
void runMainGame();

#endif