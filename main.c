/*	Maze game
*	
*	version: 0.0.1
*/

#include "main_game.h"
#include "intro.h"

#include <assert.h>

int main()
{
	IntroMenu selectedMenu;

	removeCursor();

	while (1)
	{
		selectedMenu = showIntroScreen();
		
		switch (selectedMenu)
		{
		case INTRO_MENU_PLAY_GAME: 
			runMainGame();
			break;
		case INTRO_MENU_SHOW_SCORE:
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