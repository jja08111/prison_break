#include "main_game.h"

void runMainGame()
{
	clock_t curTime, prevTime;
	unsigned char keybdInput;
	Stage stage;
	Player player;
	Map map;

	prevTime = clock();

	init(&stage, &player, &map);

	while (1)
	{
		if (_kbhit()) {
			keybdInput = _getch();

			switch (keybdInput) {
			case KEYBD_UP:
			case KEYBD_DOWN:
			case KEYBD_LEFT:
			case KEYBD_RIGHT:
				updatePlayerPosition(&player, &map, keybdInput);
				break;
			case KEYBD_ESC:
				// TODO : 게임을 종료하시겠습니까? 처리 함수 제작
				break;
			default:
				keybdInput = 0;
			}
		}

		update(&stage, &player, &map);
		render(&stage, &player, &map);

		// 1초에 약 30 프레임
		while (1) {
			curTime = clock();
			if (curTime - prevTime > 33) {
				prevTime = curTime;
				break;
			}
		}
	}
}