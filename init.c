#include "init.h"

// 맵을 단계에 맞게 초기화한다.
void initMap(Map* map, const Stage* const stage)
{
	map->height = map->width = getMapLineLength(stage);
	map->hasInitRendered = 0;
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	generateMap(1, 1, map);

	map->grid[map->height - 1][map->width - 1] = FLAG_TARGET;
}

static void _initPlayer(Player* player, const Stage* const stage)
{
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };
	player->life = 5;
	player->visionRange = visionRangeOf(stage);
	player->visionPattern = VISION_DEFAULT;
}

static void _initStage(Stage* stage)
{
	stage->level = 0;
	stage->timeLimit = timeLimitOf(stage);
	stage->score = 0;
}

void init(Stage* stage, Player* player, Map* map)
{
	srand(time(NULL));
	removeCursor();

	_initStage(stage);
	_initPlayer(player, stage);
	initMap(map, stage);
}