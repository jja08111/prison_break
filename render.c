#include "render.h"

static void _renderInitMap(const Map* const map, const Player* const player)
{
	int i, j;
	int visionRange = player->visionRange + INIT_PLAYER_POS;
	// TODO : ���� �������� �׸��� ����� �ƴ�
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
	// ���� ��ġ�� �ٸ��� �����.
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

	// �ʱ� ������
	if (isInitDraw)
	{
		_renderInitMap(map, player);
		_renderPlayer(player, prevPosition);
		isInitDraw = 0;
	}

	// �÷��̾ �̵��� ��� ������
	if (!samePosition(player->position, prevPosition))
	{
		_renderMap(map, player, prevPosition);
		_renderPlayer(player, prevPosition);

		prevPosition = player->position;
	}
}