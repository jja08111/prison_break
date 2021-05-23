#include "init.h"

// ���� �ܰ迡 �°� �ʱ�ȭ�Ѵ�.
void initMap(
	Map*				map,
	const Stage* const  stage
)
{
	map->height = map->width = getMapLineLengthPer(stage);
	map->hasInitRendered = 0;
	map->hasDrawedEntireMap = 0;
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	// ���� �������� �����Ͽ� ���� �����Ѵ�.
	generateMap(map->height - 1, map->width - 1, map);

	map->grid[map->height - 1][map->width - 1] = FLAG_TARGET;

	generateItem(map, FLAG_UNLIMIT_VISION_ITEM, 4);
}

static void _initPlayer(
	Player*				player,
	const Stage* const	stage
)
{
	player->direction = player->prevDirection = INIT_PLAYER_DIRECTION;
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };
	player->visionItemAcquiredTime = VISION_ITEM_EMPTY;
}

static void _initStage(Stage* stage)
{
	stage->level = 0;
	stage->timeLimit = getTimeLimitPer(stage);
	stage->score = 0;
}

static void _initMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Stage* const	stage,
	const Map* const	map
)
{
	mobHandler->count = 0;
	generateMob(mobHandler, INIT_MOB_NUM, player, stage, map);
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
	_initMob(mobHandler, player, stage, map);
}