#ifndef __MAP_H__
#define __MAP_H__

#include "stage.h"
#include "icons.h"
#include "colors.h"

#include <time.h>
#include <string.h>

#define MAX_HEIGHT 91
#define MAX_WIDTH 91

enum MapFlag { FLAG_WALL, FLAG_EMPTY, FLAG_VISITED };

// 맵 데이터 구조이다. 
// 
// grid에 실제 정보를 저장하고 높이와 너비값에 따라 크기가 정해진다.
typedef struct {
	int grid[MAX_HEIGHT][MAX_WIDTH];
	int height;
	int width;
} Map;

// 0단계 51
// 1단계 61
// 2단계 71
// 3단계 81
// 4단계 91 
int _getMapLineLength(const Stage* const stage);
int _shuffleArray(int array[], int size);
int _inRange(int y, int x, const Map* const map);
// 깊이우선탐색을 하면서 맵을 형성한다.
void _dfs(int y, int x, Map* const map);

void generateMap(Map* map, const Stage* const stage);
void printMap(const Map* const map);

int canPlace(COORD position, const Map* const map);

#endif