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
		// TODO : ������ �����Ͻðڽ��ϱ�?  ����
		break;
	}
}

void runMainGame()
{
	Stage stage;
	Player player;
	MobHandler mobHandler;
	Map map;
	COORD newPlayerPosition = { INIT_PLAYER_POS, INIT_PLAYER_POS };
	Direction newPlayerDirection = INIT_PLAYER_DIRECTION;

	init(&stage, &player, &mobHandler, &map);

	while (1)
	{
		if (_kbhit())
		{
			_handleKeybdHit(&newPlayerPosition, &newPlayerDirection, &map);
		}

		update(&stage, &player, &mobHandler, &map, 
			&newPlayerPosition, &newPlayerDirection);

		render(&stage, &player, &mobHandler, &map);

		Sleep(16);
	}
}