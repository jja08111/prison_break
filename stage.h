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

// 0�ܰ� 10
// 1�ܰ� 8
// 2�ܰ� 6
// 3�ܰ� 4
// 4�ܰ� 2 
int visionRangeOf(const Stage* const stage);

// 0�ܰ� 60
// 1�ܰ� 80
// 2�ܰ� 100
// 3�ܰ� 120
// 4�ܰ� 140 
int timeLimitOf(const Stage* const stage);

#endif