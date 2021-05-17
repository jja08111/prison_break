#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"
#include "player.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER_UP		"¡ã"
#define ICON_PLAYER_DOWN	"¡å"
#define ICON_PLAYER_LEFT	"¢¸"
#define ICON_PLAYER_RIGHT	"¢º"

#define ICON_MOB			"¢À"
#define ICON_TARGET			"¡ß"
#define ICON_WALL			"¡á"
#define ICON_EMPTY			"  "

void drawPlayerIcon(const Player* const player);
void drawMobIcon();
void drawTargetIcon();
void drawWallIcon();
void drawEmptyIcon();

#endif