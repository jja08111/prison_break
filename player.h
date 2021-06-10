#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "map.h"
#include "utils.h"

#include <time.h>

#define INIT_PLAYER_DIRECTION	DIRECTION_RIGHT
#define INIT_PLAYER_POS			1
#define TARGET_VISION_RANGE		1

#define MOB_KILLING_SCORE		10

typedef enum {
	STATE_NORMAL,
	STATE_SUCCESS,
	STATE_ALL_CLEAR,
	STATE_CAUGHTED
} PlayerState;

// �÷��̾��� ������ ������ �ִ�.
//
// ����, ��ġ, �׸��� �þ� ������ �����ۿ� ���� ������ ���� �ִ�.
typedef struct {
	PlayerState state;

	Direction direction;
	Direction prevDirection;

	// �÷��̾��� ���� ��ġ ��ǥ�̴�.
	// 
	// �ʱ� ��ġ�� {1,1}�̴�.
	COORD position;
	// �÷��̾��� ���� ��ġ�̴�.
	COORD prevPosition;

	// �þ� ������ �������� ���� �ð��̴�.
	//
	// ���� �ð��� UNLIMIT_VISION_DURATION(5)�� �̸�, �������� 
	// ���� ��� �� ���� -1�̴�.
	clock_t visionItemAcquiredTime;

	int killingCount;
} Player;


// �÷��̾ ���� ������ ���������� 1�� ��ȯ�Ѵ�.
int onReachedTargetPoint(
	const Player* const player,
	const Map* const	map
);

SMALL_RECT getRectFromPlayerPosition(
	const Player* const player,
	const Map* const	map,
	int					diameter
);

SMALL_RECT getPlayerPreviousVisionRect(
	const Player* const player,
	const Map* const	map
);

// �÷��̾��� �þ� �簢���� ��ȯ�Ѵ�.
SMALL_RECT getPlayerVisionRect(
	const Player* const player,
	const Map* const	map
);

int hasPlayerVisionItem(const Player* const player);

int getVisionItemLeftTimePercent(const Player* const player);

#endif