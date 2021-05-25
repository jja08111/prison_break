#include "map.h"

int getMapLineLength(const Stage* const stage)
{
	switch (stage->level) {
	case 0: return 20;
	case 1: return 30;
	case 2: return 40;
	case 3: return 50;
	case MAX_LEVEL: return 60;
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

void generateItem(
	Map*	map,
	MapFlag itemFlag,
	int		count
)
{
	int x, y, i;

	for (i = 0;i < count;++i)
	{
		x = OBJECT_GEN_PADDING + rand() % (map->width - OBJECT_GEN_PADDING * 2);
		y = OBJECT_GEN_PADDING + rand() % (map->height - OBJECT_GEN_PADDING * 2);

		// 홀수 칸에만 배치한다.
		if (x % 2 == 0)
			x--;
		if (y % 2 == 0)
			y--;

		// 이미 해당 위치에 동일한 아이템이 있는 경우 
		if (map->grid[y][x] == itemFlag)
		{
			--i;
			continue;
		}
		map->grid[y][x] = itemFlag;
	}
}

int canPlace(COORD position, const Map* const map)
{
	int inRange = (0 < position.X && position.X < map->width
		&& 0 < position.Y && position.Y < map->height);
	int isCellEmpty = map->grid[position.Y][position.X] != FLAG_WALL;

	return inRange && isCellEmpty;
}

int* getMapCellPtrFrom(
	COORD			 position,
	const Map* const map
)
{
	return &map->grid[position.Y][position.X];
}

COORD getTargetPosition(const Map* const map)
{
	return (COORD) { map->width - 1, map->height - 1 };
}

SMALL_RECT getMapRect(const Map* const map)
{
	return (SMALL_RECT) { 0, 0, map->width, map->height };
}

SMALL_RECT getMapScreenRect(const Map* const map)
{
	int x = map->topLeftPosition.X;
	int y = map->topLeftPosition.Y;
	return (SMALL_RECT) { x, y, map->width + x, map->height + y };
}

COORD getMapCenterPoint(const Map* const map)
{
	return (COORD) { map->width / 2, map->height / 2 };
}

COORD getMapScreenCenterPoint(const Map* const map)
{
	int x = map->topLeftPosition.X;
	int y = map->topLeftPosition.Y;
	return (COORD) { x + (map->width / 2), y + (map->height / 2) };
}

COORD getScreenPostion(COORD position, const Map* const map)
{
	return (COORD) {
		position.X + map->topLeftPosition.X,
		position.Y + map->topLeftPosition.Y
	};
}