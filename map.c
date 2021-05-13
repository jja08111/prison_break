#include "map.h"

// 상, 하, 좌, 우
enum { N, S, W, E};

// 상, 하, 좌, 우 이때 벽을 고려하여 2칸씩으로 설정한다.
const int DIR[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

int _getMapLineLength(const Stage* const stage)
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

// 깊이우선탐색을 하면서 맵을 형성한다.
void _dfs(int y, int x, Map* const map)
{
	int directions[4] = { N, E, S, W };

	map->grid[y][x] = FLAG_VISITED;
	// 방향을 무작위로 섞는다.
	_shuffleArray(directions, 4);

	for (int i = 0; i < 4; i++)
	{
		// 다음 위치를 구한다.
		int nx = x + DIR[directions[i]][0];
		int ny = y + DIR[directions[i]][1];
		
		if (_inRange(ny, nx, map) && map->grid[ny][nx] == FLAG_WALL) {
			_dfs(ny, nx, map);
			// 세로 축 이동
			if (ny != y)
				map->grid[(ny + y) / 2][x] = FLAG_EMPTY;
			// 가로 축 이동
			else
				map->grid[y][(x + nx) / 2] = FLAG_EMPTY;
			map->grid[ny][nx] = FLAG_EMPTY;
		}
	}
}

// 맵을 단계에 맞게 생성한다.
void generateMap(Map* map, const Stage* const stage)
{
	map->height = map->width = _getMapLineLength(stage);
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	_dfs(1, 1, map);
}

// 맵 전체를 출력한다.
void printMap(const Map* const map) 
{
	// TODO : 맵을 라인으로 그리기 블록이 아닌
	for (int i = 0;i < map->height;++i)
	{
		for (int j = 0;j < map->width;++j) {
			map->grid[i][j] == FLAG_WALL
				? printWallIcon()
				: printEmptyIcon();
		}
		printf("\n");
	}
}

int canPlace(COORD position, const Map* const map)
{
	int inRange = (0 < position.X && position.X < map->width
		&& 0 < position.Y && position.Y < map->height);
	int inEmptyCell = map->grid[position.Y][position.X] != FLAG_WALL;
	
	return inRange && inEmptyCell;
}