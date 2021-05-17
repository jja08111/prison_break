#ifndef __MAP_H__
#define __MAP_H__

#include "stage.h"
#include "utils.h"

#include <Windows.h>

#define MAP_MAX_HEIGHT	65
#define MAP_MAX_WIDTH	65

enum MapFlag { 
	FLAG_WALL,
	FLAG_EMPTY,
	FLAG_VISITED, 
	FLAG_TARGET 
};

// 맵 데이터 구조이다. 
// 
// grid에 실제 정보를 저장하고 높이와 너비값에 따라 크기가 정해진다.
typedef struct {
	// 초기 맵이 그려졌는지 여부를 저장한다.
	//
	// release 과정에서 0으로 초기화 된다.
	int hasInitRendered;

	// 맵 데이터를 [y][x]로 가진 배열이다.
	//
	// FLAG_WALL인 경우 벽이며 그 외의 경우는 빈 공간이다.
	int grid[MAP_MAX_HEIGHT][MAP_MAX_WIDTH];

	int height;
	int width;
} Map;

// 0단계 48
// 1단계 52
// 2단계 56
// 3단계 60
// 4단계 64
int getMapLineLength(const Stage* const stage);

static void _shuffleArray(int array[], int size);
static int _inRange(int y, int x, const Map* const map);
void generateMap(int y, int x, Map* const map);

// position 위치에 위치가능한 지 반환한다. 
//
// 해당 위치의 map->grid가 FLAG_WALL인 경우와
// 맵 범위를 벗어난 경우 0을 반환한다.
int canPlace(COORD position, const Map* const map);

COORD getTargetPosition(const Map* const map);

SMALL_RECT getRectOf(const Map* const map);

COORD getMapCenterPoint(const Map* const map);

#endif