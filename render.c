#include "render.h"

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int i, j;
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	// TODO : 맵을 라인으로 그리기 블록이 아닌
	for (i = 0;i < map->height;++i)
	{
		for (j = 0;j < map->width;++j)
		{
			if (i <= visionRange && j <= visionRange && map->grid[i][j] == FLAG_WALL)
				printWallIcon();
			else
				printEmptyIcon();
		}
		printf("\n");
	}
}

static void _renderMap(const Map* const map, const Player* const player, COORD prevPosition)
{
	
}

static void _renderPlayer(const Player* const player, COORD prevPosition)
{
	// 이전 위치와 다르면 지운다.
	if (!samePosition(player->position, prevPosition))
	{
		gotoPosition(prevPosition);
		printEmptyIcon();
	}

	gotoPosition(player->position);
	printPlayerIcon();
}

void render(const Stage* const stage, const Player* const player, const Map* const map)
{
	static int isInitDraw = 1;
	static COORD prevPosition = { INIT_PLAYER_POS,INIT_PLAYER_POS };

	// 초기 렌더링
	if (isInitDraw)
	{
		_renderInitMap(map, player);
		_renderPlayer(player, prevPosition);
		isInitDraw = 0;
	}

	// 플레이어가 이동한 경우 렌더링
	if (!samePosition(player->position, prevPosition))
	{
		_renderMap(map, player, prevPosition);
		_renderPlayer(player, prevPosition);

		prevPosition = player->position;
	}
}