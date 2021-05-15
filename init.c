#include "init.h"

// 상, 하, 좌, 우
static enum { N, S, W, E };

// 상, 하, 좌, 우 이때 벽을 고려하여 2칸씩으로 설정한다.
static const int DIR[4][2] = { {0,-2},{0,2},{-2,0},{2,0} };

static int _getMapLineLength(const Stage* const stage)
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
	return (y < map->height&& y >= 0) && (x < map->width&& x >= 0);
}

// 깊이우선탐색을 하면서 맵을 형성한다.
//
// 초기에는 모두 벽으로 되어있다. 방문하지 않은 정점을 탐색하며 방문한 정점을 
// 표시한다. 방문 후에는 길을 뚫어 맵을 형성한다.
static void _generateMapUsingDFS(int y, int x, Map* const map)
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
			_generateMapUsingDFS(ny, nx, map);
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
static void _initMap(Map* map, const Stage* const stage)
{
	map->height = map->width = _getMapLineLength(stage);
	map->hasInitRendered = 0;
	memset(map->grid, FLAG_WALL, sizeof(map->grid));

	_generateMapUsingDFS(1, 1, map);
}

static void _initPlayer(Player* player, const Stage* const stage)
{
	player->position = player->prevPosition = (COORD){ INIT_PLAYER_POS,INIT_PLAYER_POS };
	player->life = 5;
	player->visionRange = visionRangeOf(stage);
	player->visionPattern = VISION_DEFAULT;
}

static void _initStage(Stage* stage)
{
	stage->level = 0;
	stage->timeLimit = timeLimitOf(stage);
	stage->score = 0;
}

void init(Stage* stage, Player* player, Map* map)
{
	srand(time(NULL));
	removeCursor();

	_initStage(stage);
	_initPlayer(player, stage);
	_initMap(map, stage);
}