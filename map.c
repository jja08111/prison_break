#include "map.h"

// position 위치에 위치가능한 지 반환한다. 
//
// 해당 위치의 map->grid가 FLAG_WALL인 경우 위치할 수 없다.
int canPlace(COORD position, const Map* const map)
{
	int inRange = (0 < position.X && position.X < map->width
		&& 0 < position.Y && position.Y < map->height);
	int inEmptyCell = map->grid[position.Y][position.X] != FLAG_WALL;

	return inRange && inEmptyCell;
}

COORD getTargetPosition(const Map* const map)
{
	return (COORD) { map->width - 1, map->height - 1 };
}