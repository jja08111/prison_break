#include "main_game.h"

void init(Stage* stage, Player* player, Map* map)
{
	srand(time(NULL));
	removeCursor();

	initStage(stage);
	initPlayer(player);
	generateMap(map, stage);

	printMap(map);
	printPlayer(player);
}

void runMainGame()
{
	Stage stage;
	Player player;
	Map map;
	unsigned char keybdInput;

	init(&stage, &player, &map);

	while (1)
	{
		if (kbhit() == 1) {
			keybdInput = getch();

			switch (keybdInput) {
			case KEYBD_UP:
			case KEYBD_DOWN:
			case KEYBD_LEFT:
			case KEYBD_RIGHT:
				movePlayer(&player, &map, keybdInput);
				break;
			case KEYBD_ESC:
				// TODO : 게임을 종료하시겠습니까? 처리 함수 제작
				break;
			}
		}
	}
}