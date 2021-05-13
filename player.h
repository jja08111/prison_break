#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "utils.h"
#include "icons.h"
#include "colors.h"
#include "constants.h"
#include "map.h"

#include <stdio.h>
#include <Windows.h>

// 플레이어의 정보를 가지고 있다.
//
// 멤버변수로 position, life, score를 가지고 있다. 이때 position은 COORD 구조체이며,
// 이 구조체는 멤버변수로 X,Y를 가지고 있다.
typedef struct {
	COORD position;
	short life;
	int score;
} Player;

void _gotoPosition(COORD position);

void initPlayer(Player* player);
void printPlayer(const Player* const player);
void movePlayer(Player* player, const Map* const map, unsigned char keybdInput);

#endif