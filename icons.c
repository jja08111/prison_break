#include "icons.h"

void drawPlayerIcon()
{
	setPlayerIconColor();
	printf("%s", ICON_PLAYER);
}

void drawWallIcon()
{
	setWallIconColor();
	printf("%s", ICON_WALL);
}

void drawEmptyIcon()
{
	setEmptyIconColor();
	printf("%s", ICON_EMPTY);
}

void drawBombIcon()
{
	setBombIconColor();
	printf("%s", ICON_BOMB);
}