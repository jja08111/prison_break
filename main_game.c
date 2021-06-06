#include "main_game.h"

static void _handleKeybdHit(
	COORD*			 newPosition, 
	Direction*		 newDirection,
	const Map* const map
)
{
	unsigned char keybdInput;

	keybdInput = _getch();
	switch (keybdInput) {
	case KEYBD_UP:
	case KEYBD_DOWN:
	case KEYBD_LEFT:
	case KEYBD_RIGHT:
		*newDirection = updatePositionByInput(newPosition, map, keybdInput);
		break;
	case KEYBD_ESC:
		// TODO : 게임을 종료하시겠습니까?  제작
		break;
	}
}

void runMainGame()
{
	Stage stage;
	Player player;
	MobHandler mobHandler;
	Map map;
	SoundController soundController;

	COORD newPlayerPosition = { INIT_PLAYER_POS, INIT_PLAYER_POS };
	Direction newPlayerDirection = INIT_PLAYER_DIRECTION;

	init(&stage, &player, &mobHandler, &map, &soundController);

	while (1)
	{
		if (_kbhit())
		{
			_handleKeybdHit(&newPlayerPosition, &newPlayerDirection, &map);
		}

		update(&stage, &player, &mobHandler, &map, &soundController,
			&newPlayerPosition, &newPlayerDirection);

		render(&stage, &player, &mobHandler, &map);

		if (player.state == STATE_CAUGHTED)
			break;

		Sleep(16);
	}

	renderScoreInputDialog(&map, &stage, &player);
	
	removeCursor();

	clearScreen();
}