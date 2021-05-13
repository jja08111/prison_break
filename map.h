#ifndef __MAP_H__
#define __MAP_H__

#include "stage.h"

#define MAX_HEIGHT 91
#define MAX_WIDTH 91
#define WALL "■"
#define EMPTY_CELL "  "

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
int mapLineLengthOf(const Stage* const stage);

void generateMap(Map* map, const Stage* const stage);

void printMap(const Map* const map);

#endif