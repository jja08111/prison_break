#ifndef __MAP_H__
#define __MAP_H__

#include "stage.h"
#include "utils.h"
#include "constants.h"

#include <Windows.h>

#define MAP_MAX_HEIGHT		42
#define MAP_MAX_WIDTH		42

#define OBJECT_GEN_PADDING	3

#define VISION_ITEM_DURATION	5000 // 5초
#define VISION_ITEM_EMPTY		-1	 // -1

typedef enum _MapFlag {
	FLAG_WALL,
	FLAG_EMPTY,
	FLAG_VISITED, 

	FLAG_TARGET,

	FLAG_MOB_VISION,

	FLAG_UNLIMIT_VISION_ITEM
} MapFlag;

// 맵 데이터 구조이다. 
// 
// grid에 실제 정보를 저장하고 높이와 너비값에 따라 크기가 정해진다.
typedef struct {
	// 초기 맵이 그려졌는지 여부를 저장한다.
	//
	// release 과정에서 0으로 초기화 된다.
	int hasInitRendered;

	// 전체 맵이 렌더링 되면 1을 저장한다.
	//
	// unlimit_vision_item을 위해 사용한다.
	int hasDrawedEntireMap;

	// 맵 데이터를 [y][x]로 가진 배열이다.
	//
	// FLAG_WALL인 경우 벽이며 그 외의 경우는 빈 공간이다.
	int grid[MAP_MAX_HEIGHT][MAP_MAX_WIDTH];

	int height;
	int width;

	COORD topLeftPosition;
} Map;

void setMapSize(
	Map* map,
	const Stage* const stage
);

COORD getGeneratingStartPoint(const Map* const map);

void generateMap(int y, int x, Map* const map);

// 맵의 grid에 아이템 flag를 무작위 위치에 저장한다.
void generateItem(
	Map*	map,
	MapFlag item,
	int		count
);

// position 위치에 위치가능한 지 반환한다. 
//
// 해당 위치의 map->grid가 FLAG_WALL인 경우와
// 맵 범위를 벗어난 경우 0을 반환한다.
int canPlace(COORD position, const Map* const map);

int* getMapCellPtrFrom(
	COORD position,
	Map*  map
);

int isTargetPoint(COORD position, const Map* const map);

COORD getTargetPosition(const Map* const map);

SMALL_RECT getMapRect(const Map* const map);

SMALL_RECT getMapScreenRect(const Map* const map);

COORD getMapCenterCoord(const Map* const map);

COORD getMapScreenCenterPoint(const Map* const map);

COORD getScreenPostion(COORD position, const Map* const map);

#endif