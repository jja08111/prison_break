#include "map.h"

#include <time.h>
#include <string.h>
#include <stdio.h>

// ��, ��, ��, ��
enum { N, S, W, E};

// ��, ��, ��, �� �̶� ���� ����Ͽ� 2ĭ������ �����Ѵ�.
const int DIR[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

int mapLineLengthOf(const Stage* const stage)
{
	switch (stage->level) {
	case 0: return 51;
	case 1: return 61;
	case 2: return 71;
	case 3: return 81;
	case MAX_LEVEL: return 91;
	}
	return 0;
}

int _shuffleArray(int array[], int size) 
{
	for (int i = 0;i < (size - 1);++i)
	{
		int r = i + (rand() % (size - i));
		int temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}

int _inRange(int y, int x, const Map* const map)
{
	return (y < map->height&& y >= 0) && (x < map->width && x >= 0);
}

// ���̿켱Ž���� �ϸ鼭 ���� �����Ѵ�.
void _dfs(int y, int x, Map* const map)
{
	int directions[4] = { N, E, S, W };

	map->grid[y][x] = FLAG_VISITED;
	// ������ �������� ���´�.
	_shuffleArray(directions, 4);

	for (int i = 0; i < 4; i++)
	{
		// ���� ��ġ�� ���Ѵ�.
		int nx = x + DIR[directions[i]][0];
		int ny = y + DIR[directions[i]][1];
		
		if (_inRange(ny, nx, map) && map->grid[ny][nx] == FLAG_WALL) {
			_dfs(ny, nx, map);
			// ���� �� �̵�
			if (ny != y)
				map->grid[(ny + y) / 2][x] = FLAG_EMPTY;
			// ���� �� �̵�
			else
				map->grid[y][(x + nx) / 2] = FLAG_EMPTY;
			map->grid[ny][nx] = FLAG_EMPTY;
		}
	}
}

// ���� �ܰ迡 �°� �����Ѵ�.
void generateMap(Map* map, const Stage* const stage)
{
	map->height = map->width = mapLineLengthOf(stage);
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	_dfs(1, 1, map);
}

// �� ��ü�� ����Ѵ�.
void printMap(const Map* const map) 
{
	for (int i = 0;i < map->height;++i)
	{
		for (int j = 0;j < map->width;++j)
			printf("%s", map->grid[i][j] == FLAG_WALL ? WALL : EMPTY_CELL);
		printf("\n");
	}
}