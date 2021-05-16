#ifndef __MAP_H__
#define __MAP_H__

#include <Windows.h>

#define MAX_HEIGHT 91
#define MAX_WIDTH 91

enum MapFlag { FLAG_WALL, FLAG_EMPTY, FLAG_VISITED, FLAG_TARGET };

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
	int grid[MAX_HEIGHT][MAX_WIDTH];

	int height;
	int width;
} Map;

// position 위치에 위치가능한 지 반환한다. 
//
// 해당 위치의 map->grid가 FLAG_WALL인 경우 위치할 수 없다.
int canPlace(COORD position, const Map* const map);

COORD getTargetPosition(const Map* const map);

#endif