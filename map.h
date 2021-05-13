#ifndef __MAP_H__
#define __MAP_H__

#include "stage.h"

#define MAX_HEIGHT 91
#define MAX_WIDTH 91
#define WALL "��"
#define EMPTY_CELL "  "

enum MapFlag { FLAG_WALL, FLAG_EMPTY, FLAG_VISITED };

// �� ������ �����̴�. 
// 
// grid�� ���� ������ �����ϰ� ���̿� �ʺ񰪿� ���� ũ�Ⱑ ��������.
typedef struct {
	int grid[MAX_HEIGHT][MAX_WIDTH];
	int height;
	int width;
} Map;

// 0�ܰ� 51
// 1�ܰ� 61
// 2�ܰ� 71
// 3�ܰ� 81
// 4�ܰ� 91 
int mapLineLengthOf(const Stage* const stage);

void generateMap(Map* map, const Stage* const stage);

void printMap(const Map* const map);

#endif