#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"
#include "player.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER_UP		"��"
#define ICON_PLAYER_DOWN	"��"
#define ICON_PLAYER_LEFT	"��"
#define ICON_PLAYER_RIGHT	"��"

#define ICON_MOB			"��"
#define ICON_TARGET			"��"
#define ICON_WALL			"��"
#define ICON_EMPTY			"  "

void drawPlayerIcon(const Player* const player);
void drawMobIcon();
void drawTargetIcon();
void drawWallIcon();
void drawEmptyIcon();

#endif