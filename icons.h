#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"
#include "models.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER_UP				"¡ã"
#define ICON_PLAYER_DOWN			"¡å"
#define ICON_PLAYER_LEFT			"¢¸"
#define ICON_PLAYER_RIGHT			"¢º"

#define ICON_VISION_ITEM			"¢À"
#define ICON_EXHAUST_ITEM			"¢Í"
#define ICON_TARGET					"¡ß"
#define ICON_WALL					"¡á"
#define ICON_EMPTY					"  "

void drawPlayerIcon(const Player* const player);
void drawPlayerIconWithNoColor(const Player* const player);
void drawMobIcon(const Mob* const mob);
void drawTargetIcon();
void drawWallIcon();
void drawWallIconWith(int backgroundColor);
void drawEmptyIcon();
void drawEmptyIconWithNoColor();
void drawVisionItemIconWith(int backgroundColor);
void drawExhaustItemIconWith(int backgroundColor);

#endif