#include "init.h"

static void _initSound(SoundController* controller)
{
	setHeartBeatLoopSound(controller);
	clearNextSound(controller);
}

// ���� �ܰ迡 �°� �ʱ�ȭ�Ѵ�.
void initMap(
	Map*				map,
	const Stage* const  stage
)
{
	setMapSize(map, stage);

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
	player->state = STATE_NORMAL;
	player->direction = player->prevDirection = INIT_PLAYER_DIRECTION;
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };
	player->visionItemAcquiredTime = VISION_ITEM_EMPTY;

	player->killingCount = 0;
	player->prevKillingCount = -1;
}

static void _initStage(Stage* stage)
{
	stage->level = 0;

	stage->score = getStageStartScore(stage);
	stage->prevScore = -1;

	stage->scoreUpdateTime = clock();

	stage->totalScore = 0;
	stage->prevTotalScore = -1;
}

static void _initMob(
	MobHandler*			mobHandler,
	const Player* const player,
	const Stage* const	stage,
	const Map* const	map
)
{
	mobHandler->count = 0;
	generateMob(mobHandler, getMobCountPer(stage), player, stage, map);
}

void init(
	Stage*			 stage,
	Player*			 player,
	MobHandler*		 mobHandler,
	Map*			 map,
	SoundController* soundController
)
{
	_initSound(soundController);
	_initStage(stage);
	initMap(map, stage);
	_initPlayer(player, stage);
	_initMob(mobHandler, player, stage, map);
}