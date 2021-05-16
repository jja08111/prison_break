#include "map.h"

// position ��ġ�� ��ġ������ �� ��ȯ�Ѵ�. 
//
// �ش� ��ġ�� map->grid�� FLAG_WALL�� ��� ��ġ�� �� ����.
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