#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "utils.h"
#include "icons.h"
#include "colors.h"
#include "constants.h"
#include "map.h"

#include <stdio.h>
#include <Windows.h>

// �÷��̾��� ������ ������ �ִ�.
//
// ��������� position, life, score�� ������ �ִ�. �̶� position�� COORD ����ü�̸�,
// �� ����ü�� ��������� X,Y�� ������ �ִ�.
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