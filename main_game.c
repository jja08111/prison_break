#include "main_game.h"
#include "init.h"

void runMainGame()
{
	Map map;
	Stage stage = { 0,10,60 };

	srand(time(NULL));
	init(&map, &stage);

	while (1)
	{
		printMap(&map);
		int temp;
		scanf("%d", &temp);
	}
}