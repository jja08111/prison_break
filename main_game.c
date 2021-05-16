#include "main_game.h"

void runMainGame()
{
	clock_t curTime, prevTime;
	unsigned char keybdInput;
	Stage stage;
	Player player;
	Map map;
	COORD newPosition = { INIT_PLAYER_POS, INIT_PLAYER_POS };

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
				updatePosition(&newPosition, &map, keybdInput);
				break;
			case KEYBD_ESC:
				// TODO : ������ �����Ͻðڽ��ϱ�? ó�� �Լ� ����
				break;
			default:
				keybdInput = 0;
			}
		}

		update(&stage, &player, &map, newPosition);
		render(&stage, &player, &map);

		// 1�ʿ� �� 30 ������
		while (1) {
			curTime = clock();
			if (curTime - prevTime > 33) {
				prevTime = curTime;
				break;
			}
		}
	}
}