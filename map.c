#include "map.h"

int getMapLineLengthPer(const Stage* const stage)
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

// 상, 하, 좌, 우 이때 벽을 고려하여 2칸씩으로 설정한다.
static const int DIR[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

static void _shuffleArray(int array[], int size)
{
	int i, r, temp;

	for (i = 0;i < (size - 1);++i)
	{
		r = i + (rand() % (size - i));
		temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}

static int _inRange(int y, int x, const Map* const map)
{
	return (y <= map->height && y >= 0) && (x <= map->width && x >= 0);
}

// (x,y)부터 깊이우선탐색을 하며 맵을 형성한다.
//
// 초기에는 모두 벽으로 되어있다. 방문하지 않은 정점을 탐색하며 방문한 정점을 
// 표시한다. 방문 후에는 길을 뚫어 맵을 형성한다.
void generateMap(int y, int x, Map* const map)
{
	int i, nx, ny;
	int directions[4] = { 
		DIRECTION_UP, 
		DIRECTION_RIGHT,
		DIRECTION_DOWN, 
		DIRECTION_LEFT
	};

	map->grid[y][x] = FLAG_VISITED;
	// 방향을 무작위로 섞는다.
	_shuffleArray(directions, 4);

	for (i = 0; i < 4; i++)
	{
		// 다음 위치를 구한다.
		nx = x + DIR[directions[i]][0];
		ny = y + DIR[directions[i]][1];

		if (_inRange(ny, nx, map) && map->grid[ny][nx] == FLAG_WALL) {
			generateMap(ny, nx, map);
			// 세로 축 이동인 경우
			if (ny != y)
				map->grid[(ny + y) / 2][x] = FLAG_EMPTY;
			// 가로 축 이동인 경우
			else
				map->grid[y][(x + nx) / 2] = FLAG_EMPTY;
			map->grid[ny][nx] = FLAG_EMPTY;
		}
	}
}

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

SMALL_RECT getRectOf(const Map* const map)
{
	return  (SMALL_RECT) { 0, 0, map->width, map->height };
}

COORD getMapCenterPoint(const Map* const map)
{
	return (COORD) { map->width / 2, map->height / 2 };
}