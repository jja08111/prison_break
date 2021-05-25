#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"
#include "models.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER_UP				"��"
#define ICON_PLAYER_DOWN			"��"
#define ICON_PLAYER_LEFT			"��"
#define ICON_PLAYER_RIGHT			"��"

#define ICON_VISION_ITEM			"��"
#define ICON_TARGET					"��"
#define ICON_WALL					"��"
#define ICON_EMPTY					"  "

static void _drawDirectionIcon(Direction direction);

void drawPlayerIcon(const Player* const player);
void drawPlayerIconWithNoColor(const Player* const player);
void drawMobIcon(const Mob* const mob);
void drawTargetIcon();
void drawWallIcon();
void drawWallIconWith(int backgroundColor);
void drawEmptyIcon();
void drawEmptyIconWithNoColor();
void drawVisionItemIcon();
void drawVisionItemIconWith(int backgroundColor);

#endif