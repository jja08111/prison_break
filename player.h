#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"
#include "utils.h"

#define INIT_PLAYER_POS 1
#define TARGET_VISION_RANGE 2

enum VisionPattern { VISION_DEFAULT };

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

	short visionRange;

	enum VisionPattern visionPattern;
} Player;

int onReachedTargetPoint(const Player* const player, const Map* const map);


#endif