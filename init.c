#include "init.h"

// 맵을 단계에 맞게 초기화한다.
void initMap(
	Map*				map,
	const Stage* const  stage
)
{
	map->height = map->width = getMapLineLength(stage);
	map->hasInitRendered = 0;
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	// 도착 지점부터 시작하여 맵을 생성한다.
	generateMap(map->height - 1, map->width - 1, map);

	map->grid[map->height - 1][map->width - 1] = FLAG_TARGET;
}

static void _initPlayer(
	Player*				player,
	const Stage* const	stage
)
{
	player->direction = player->prevDirection = INIT_PLAYER_DIRECTION;
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

static void _initMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Map* const	map
)
{
	mobHandler->count = 0;
	generateMob(mobHandler, INIT_MOB_NUM, player, map);
}

void init(
	Stage*		stage,
	Player*		player,
	MobHandler* mobHandler,
	Map*		map
)
{
	srand((unsigned int)time(NULL));
	removeCursor();

	_initStage(stage);
	initMap(map, stage);
	_initPlayer(player, stage);
	_initMob(mobHandler, player, map);
}