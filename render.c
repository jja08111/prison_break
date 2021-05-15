#include "render.h"

// 플레이어 시야 범위내에 (x,y)가 위치했으면 1을, 아니면 0을 반환한다.
static int _inVisionRange(int y, int x, const Map* const map, const Player* const player)
{
	int visionRange = player->visionRange;
	int py = player->position.Y;
	int px = player->position.X;

	int minY = MAX(0, py - visionRange);
	int minX = MAX(0, px - visionRange);
	int maxY = MIN(map->height, py + visionRange);
	int maxX = MIN(map->width, px + visionRange);
	
	return minY <= y && y <= maxY && minX <= x && x <= maxX;
}

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int i, j;
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	// TODO : 맵을 라인으로 그리기 블록이 아닌
	for (i = 0;i < map->height;++i)
	{
		for (j = 0;j < map->width;++j)
		{
			if (_inVisionRange(i, j, map, player) && map->grid[i][j] == FLAG_WALL)
				printWallIcon();
			else
				printEmptyIcon();
		}
		printf("\n");
	}
}

// 이동한 방향의 맵을 그리며, 이전 방향 부분의 맵은 지운다.
static void _renderMap(const Map* const map, const Player* const player)
{
	
}

static void _renderPlayer(const Player* const player)
{
	// 이전 위치와 다르면 지운다.
	if (!samePosition(player->position, player->prevPosition))
	{
		gotoPosition(player->prevPosition);
		printEmptyIcon();
	}

	gotoPosition(player->position);
	printPlayerIcon();
}

void render(const Stage* const stage, const Player* const player, Map* map)
{
	if (!map->hasInitRendered)
	{
		_renderInitMap(map, player);
		_renderPlayer(player);
		map->hasInitRendered = 1;
	}

	// 플레이어가 이동한 경우 렌더링
	if (!samePosition(player->position, player->prevPosition))
	{
		_renderMap(map, player);
		_renderPlayer(player);
	}
}