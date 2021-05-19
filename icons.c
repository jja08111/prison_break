#include "icons.h"

static void _drawDirectionIcon(Direction direction)
{
	switch (direction)
	{
	case DIRECTION_UP:
		printf("%s", ICON_PLAYER_UP);
		break;
	case DIRECTION_DOWN:
		printf("%s", ICON_PLAYER_DOWN);
		break;
	case DIRECTION_LEFT:
		printf("%s", ICON_PLAYER_LEFT);
		break;
	case DIRECTION_RIGHT:
		printf("%s", ICON_PLAYER_RIGHT);
	}
}

void drawPlayerIcon(const Player* const player)
{
	textcolor(PRIMARY_COLOR, SURFACE_COLOR);
	_drawDirectionIcon(player->direction);
}

void drawMobIcon(const Mob* const mob)
{
	textcolor(ACCENT_COLOR, SURFACE_COLOR);
	_drawDirectionIcon(mob->direction);
}

void drawTargetIcon()
{
	textcolor(SECONDARY_COLOR, SURFACE_COLOR);
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

void drawNoneColoredEmptyIcon()
{
	printf("%s", ICON_EMPTY);
}