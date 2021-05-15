#ifndef __PLAYER_H__
#define __PLAYER_H__

#define INIT_PLAYER_POS 1

enum VisionPattern { VISION_DEFAULT };

// �÷��̾��� ������ ������ �ִ�.
//
// ��������� position, life, score�� ������ �ִ�. �̶� position�� COORD ����ü�̸�,
// �� ����ü�� ��������� X,Y�� ������ �ִ�.
typedef struct {
	// �÷��̾��� ���� ��ġ ��ǥ�̴�.
	// 
	// �ʱ� ��ġ�� {1,1}�̴�.
	COORD position;

	// �÷��̾��� ���� ��ġ�̴�.
	COORD prevPosition;

	short life;

	int visionRange;

	enum VisionPattern visionPattern;
} Player;

#endif