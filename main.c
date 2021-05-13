/*	Maze game
*	
*	version: 0.0.1
*/

#include "ui.h"
#include "main_game.h"

int main()
{
	system("mode con cols=166 lines=56 | title Maze game v0.0.1");

	printStartScreen();

	while (1)
	{
		runMainGame();
	}

	return 0;
}