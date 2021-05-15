#ifndef __PLAYER_H__
#define __PLAYER_H__

#define INIT_PLAYER_POS 1

// �÷��̾��� ������ ������ �ִ�.
//
// ��������� position, life, score�� ������ �ִ�. �̶� position�� COORD ����ü�̸�,
// �� ����ü�� ��������� X,Y�� ������ �ִ�.
typedef struct {
	// �÷��̾��� ���� ��ġ ��ǥ�̴�.
	// 
	// �ʱ� ��ġ�� {1,1}�̴�.
	COORD position;

	short life;

	int visionRange;
} Player;

#endif