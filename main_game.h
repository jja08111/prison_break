#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

#include "init.h"
#include "render.h"
#include "update.h"
#include "utils.h"
#include "constants.h"

#include <conio.h>
#include <time.h>
#include <stdlib.h>

static void _handleKeybdHit(COORD* newPosition, const Map* const map);

// 미로 게임을 실행한다.
void runMainGame();

#endif