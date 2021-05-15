#ifndef __PLAYER_H__
#define __PLAYER_H__

#define INIT_PLAYER_POS 1

enum VisionPattern { VISION_DEFAULT };

// 플레이어의 정보를 가지고 있다.
//
// 멤버변수로 position, life, score를 가지고 있다. 이때 position은 COORD 구조체이며,
// 이 구조체는 멤버변수로 X,Y를 가지고 있다.
typedef struct {
	// 플레이어의 현재 위치 좌표이다.
	// 
	// 초기 위치는 {1,1}이다.
	COORD position;

	// 플레이어의 이전 위치이다.
	COORD prevPosition;

	short life;

	int visionRange;

	enum VisionPattern visionPattern;
} Player;

#endif