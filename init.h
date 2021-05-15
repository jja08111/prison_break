#ifndef __INIT_H__
#define __INIT_H__

#include "map.h"
#include "stage.h"
#include "player.h"
#include "utils.h"

#include <time.h>

// 0�ܰ� 50
// 1�ܰ� 60
// 2�ܰ� 70
// 3�ܰ� 80
// 4�ܰ� 90
static int _getMapLineLength(const Stage* const stage);
static int _shuffleArray(int array[], int size);
static int _inRange(int y, int x, const Map* const map);
// ���̿켱Ž���� �ϸ鼭 ���� �����Ѵ�.
static void _generateMapUsingDFS(int y, int x, Map* const map);

static void _initMap(Map* map, const Stage* const stage);
static void _initPlayer(Player* player, const Stage* const stage);
static void _initStage(Stage* stage);

void init(Stage* stage, Player* player, Map* map);

#endif