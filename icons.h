#ifndef __ICONS_H__
#define __ICONS_H__

#include "colors.h"

#include <stdio.h>
#include <Windows.h>

#define ICON_PLAYER "¡Ü"
#define ICON_WALL "¡á"
#define ICON_EMPTY "  "
#define ICON_BOMB "¢À"

void drawPlayerIcon();
void drawWallIcon();
void drawEmptyIcon();
void drawBombIcon();

#endif