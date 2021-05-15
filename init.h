#ifndef __INIT_H__
#define __INIT_H__

#include "map.h"
#include "stage.h"
#include "player.h"
#include "utils.h"

#include <time.h>

// 0단계 50
// 1단계 60
// 2단계 70
// 3단계 80
// 4단계 90
static int _getMapLineLength(const Stage* const stage);
static int _shuffleArray(int array[], int size);
static int _inRange(int y, int x, const Map* const map);
// 깊이우선탐색을 하면서 맵을 형성한다.
static void _generateMapUsingDFS(int y, int x, Map* const map);

static void _initMap(Map* map, const Stage* const stage);
static void _initPlayer(Player* player, const Stage* const stage);
static void _initStage(Stage* stage);

void init(Stage* stage, Player* player, Map* map);

#endif