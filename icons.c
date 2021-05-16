#include "icons.h"

void drawPlayerIcon()
{
	textcolor(PRIMARY_COLOR, SURFACE_COLOR);
	printf("%s", ICON_PLAYER);
}

void drawTargetIcon()
{
	textcolor(ACCENT_COLOR, SURFACE_COLOR);
	printf("%s", ICON_TARGET);
}

void drawWallIcon()
{
	textcolor(ON_SURFACE_COLOR, SURFACE_COLOR);
	printf("%s", ICON_WALL);
}

void drawEmptyIcon()
{
	textcolor(SURFACE_COLOR, SURFACE_COLOR);
	printf("%s", ICON_EMPTY);
}

void drawBombIcon()
{
	textcolor(ACCENT_COLOR, SURFACE_COLOR);
	printf("%s", ICON_BOMB);
}