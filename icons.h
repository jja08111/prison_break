#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"
#include "player.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER_UP "��"
#define ICON_PLAYER_DOWN "��"
#define ICON_PLAYER_LEFT "��"
#define ICON_PLAYER_RIGHT "��"
#define ICON_TARGET "��"
#define ICON_WALL "��"
#define ICON_EMPTY "  "
#define ICON_BOMB "��"

void drawPlayerIcon(const Player* const player);
void drawTargetIcon();
void drawWallIcon();
void drawEmptyIcon();
void drawBombIcon();

#endif