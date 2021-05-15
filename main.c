/*	Maze game
*	
*	version: 0.0.1
*/

#include "main_game.h"

int main()
{
	system("mode con cols=166 lines=56 | title Maze game");

	while (1)
	{
		runMainGame();
	}

	return 0;
}