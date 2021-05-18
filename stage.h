#ifndef __STAGE_H__
#define __STAGE_H__

#define MAX_LEVEL 4

// �������� ������ ������ �ִ�.
//
// ��������� level, score, timeLimit�� �ִ�.
typedef struct {
	// �������� �����̴�. 
	//
	// 0���� �����Ѵ�.
	int level;
	
	// ���� ȹ���� �����̴�.
	int score;

	// �ð� �����̴�.
	int timeLimit;
} Stage;

// 0�ܰ� 60
// 1�ܰ� 80
// 2�ܰ� 100
// 3�ܰ� 120
// 4�ܰ� 140 
int getTimeLimitPer(const Stage* const stage);

#endif