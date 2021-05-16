#include "map.h"

int getMapLineLength(const Stage* const stage)
{
	switch (stage->level) {
	case 0: return 48;
	case 1: return 52;
	case 2: return 56;
	case 3: return 60;
	case MAX_LEVEL: return 64;
	}
	return 0;
}

// ��, ��, ��, ��
static enum { N, S, W, E };

// ��, ��, ��, �� �̶� ���� ����Ͽ� 2ĭ������ �����Ѵ�.
static const int DIR[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

static int _shuffleArray(int array[], int size)
{
	for (int i = 0;i < (size - 1);++i)
	{
		int r = i + (rand() % (size - i));
		int temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}

static int _inRange(int y, int x, const Map* const map)
{
	return (y <= map->height && y >= 0) && (x <= map->width && x >= 0);
}

// (x,y)���� ���̿켱Ž���� �ϸ� ���� �����Ѵ�.
//
// �ʱ⿡�� ��� ������ �Ǿ��ִ�. �湮���� ���� ������ Ž���ϸ� �湮�� ������ 
// ǥ���Ѵ�. �湮 �Ŀ��� ���� �վ� ���� �����Ѵ�.
void generateMap(int y, int x, Map* const map)
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
			generateMap(ny, nx, map);
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

// position ��ġ�� ��ġ������ �� ��ȯ�Ѵ�. 
//
// �ش� ��ġ�� map->grid�� FLAG_WALL�� ��� ��ġ�� �� ����.
int canPlace(COORD position, const Map* const map)
{
	int inRange = (0 < position.X && position.X < map->width
		&& 0 < position.Y && position.Y < map->height);
	int inEmptyCell = map->grid[position.Y][position.X] != FLAG_WALL;

	return inRange && inEmptyCell;
}

COORD getTargetPosition(const Map* const map)
{
	return (COORD) { map->width - 1, map->height - 1 };
}

SMALL_RECT getMapRect(const Map* const map)
{
	return  (SMALL_RECT) { 0, 0, map->width, map->height };
}

COORD getMapCenterPoint(const Map* const map)
{
	return (COORD) { map->width / 2, map->height / 2 };
}