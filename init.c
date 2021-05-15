#include "init.h"

// ��, ��, ��, ��
static enum { N, S, W, E };

// ��, ��, ��, �� �̶� ���� ����Ͽ� 2ĭ������ �����Ѵ�.
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

// ���̿켱Ž���� �ϸ鼭 ���� �����Ѵ�.
//
// �ʱ⿡�� ��� ������ �Ǿ��ִ�. �湮���� ���� ������ Ž���ϸ� �湮�� ������ 
// ǥ���Ѵ�. �湮 �Ŀ��� ���� �վ� ���� �����Ѵ�.
static void _generateMapUsingDFS(int y, int x, Map* const map)
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
			_generateMapUsingDFS(ny, nx, map);
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