#include "render.h"

// �÷��̾� �þ� �������� (x,y)�� ��ġ������ 1��, �ƴϸ� 0�� ��ȯ�Ѵ�.
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
	// TODO : ���� �������� �׸��� ����� �ƴ�
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

// �̵��� ������ ���� �׸���, ���� ���� �κ��� ���� �����.
static void _renderMap(const Map* const map, const Player* const player)
{
	
}

static void _renderPlayer(const Player* const player)
{
	// ���� ��ġ�� �ٸ��� �����.
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

	// �÷��̾ �̵��� ��� ������
	if (!samePosition(player->position, player->prevPosition))
	{
		_renderMap(map, player);
		_renderPlayer(player);
	}
}