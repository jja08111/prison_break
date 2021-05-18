#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"
#include "utils.h"

#define INIT_PLAYER_DIRECTION DIRECTION_RIGHT
#define INIT_PLAYER_POS 1
#define TARGET_VISION_RANGE 1

typedef enum _VisionPattern { VISION_DEFAULT } VisionPattern;

// �÷��̾��� ������ ������ �ִ�.
//
// ��������� position, life, score�� ������ �ִ�. �̶� position�� COORD ����ü�̸�,
// �� ����ü�� ��������� X,Y�� ������ �ִ�.
typedef struct {
	Direction direction;
	Direction prevDirection;

	// �÷��̾��� ���� ��ġ ��ǥ�̴�.
	// 
	// �ʱ� ��ġ�� {1,1}�̴�.
	COORD position;
	// �÷��̾��� ���� ��ġ�̴�.
	COORD prevPosition;

	short life;

	// �÷��̾��� �þ� �������̴�. 
	short visionRange;

	VisionPattern visionPattern;
} Player;

// 0�ܰ� 10
// 1�ܰ� 8
// 2�ܰ� 6
// 3�ܰ� 4
// 4�ܰ� 2 
int getPlayerVisionRangePer(const Stage* const stage);

// �÷��̾ ���� ������ ���������� 1�� ��ȯ�Ѵ�.
int onReachedTargetPoint(
	const Player* const player,
	const Map* const	map
);

SMALL_RECT getRectFromPlayer(
	const Player* const player,
	const Map* const	map,
	int					diameter
);

// �÷��̾��� �þ� �簢���� ��ȯ�Ѵ�.
SMALL_RECT getPlayerVisionRect(
	const Player* const player,
	const Map* const	map
);

#endif