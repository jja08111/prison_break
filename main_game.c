#include "main_game.h"

static void _handleKeybdHit(COORD* newPosition, const Map* const map)
{
	unsigned char keybdInput;

	keybdInput = _getch();
	switch (keybdInput) {
	case KEYBD_UP:
	case KEYBD_DOWN:
	case KEYBD_LEFT:
	case KEYBD_RIGHT:
		updatePosition(newPosition, map, keybdInput);
		break;
	case KEYBD_ESC:
		// TODO : 게임을 종료하시겠습니까? 처리 함수 제작
		break;
	}
}

void runMainGame()
{
	Stage stage;
	Player player;
	Map map;
	COORD newPosition = { INIT_PLAYER_POS, INIT_PLAYER_POS };

	init(&stage, &player, &map);

	while (1)
	{
		if (_kbhit())
		{
			_handleKeybdHit(&newPosition, &map);
		}

		update(&stage, &player, &map, &newPosition);
		render(&stage, &player, &map);

		Sleep(16);
	}
}