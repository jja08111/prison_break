#include "main_game.h"
#include "utils.h"

void init(Map* map, Stage* stage)
{
	generateMap(map, stage);
	removeCursor();
}