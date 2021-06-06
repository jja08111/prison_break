/*	
*	The Prison Break game made by Minseong Kim
*/

#include "main_game.h"
#include "intro.h"
#include "record.h"

#include <assert.h>

int main()
{
	IntroMenu selectedMenu;

	removeCursor();
	srand((unsigned int)time(NULL));
	// 화면 크기: 150 X 41(SCREEN_WIDTH, SCREEN_HIEGHT), 배경색상: 검정
	system("mode con cols=150 lines=41 | title Maze game | color 01");

	while (1)
	{
		selectedMenu = showIntroScreen();
		
		switch (selectedMenu)
		{
		case INTRO_MENU_PLAY_GAME:
			runMainGame();
			break;
		case INTRO_MENU_SHOW_SCORE:
			showRecordScreen();
			break;
		case INTRO_MENU_EXIT:
			exit(0);
			break;
		default:
			assert(0);
		}
	}

	return 0;
}