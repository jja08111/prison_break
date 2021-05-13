#include "icons.h"

void printPlayerIcon()
{
	setPlayerIconColor();
	printf("%s", ICON_PLAYER);
}

void printWallIcon()
{
	setWallIconColor();
	printf("%s", ICON_WALL);
}

void printEmptyIcon()
{
	setEmptyIconColor();
	printf("%s", ICON_EMPTY);
}