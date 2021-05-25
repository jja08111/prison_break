#include "intro.h"
#include "utils.h"
#include "constants.h"
#include "colors.h"
#include "map.h"
#include "icons.h"
#include "render.h"
#include "update.h"

#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <string.h>

#define ACTION_TOP_Y_POS 30
#define ACTION_LEFT_X_POS 35

static void initSampleMap(Map* map)
{
	map->topLeftPosition = (COORD){ 28,2 };
	map->height = 8;
	map->width = 20;
	map->hasInitRendered = 0;
	map->hasDrawedEntireMap = 0;

	memset(map->grid, FLAG_WALL, sizeof(map->grid));
	generateMap(map->height - 1, map->width - 1, map);
}

static void initSamplePlayer(Player* player)
{
	player->state = STATE_NORMAL;
	player->direction = player->prevDirection = INIT_PLAYER_DIRECTION;
	player->position = player->prevPosition = (COORD){ 0,0 };
	player->visionItemAcquiredTime = clock();
}

static void initSampleMob(
	MobHandler*			mobHandler,
	const Map* const	map
)
{
	Mob newMob;
	Direction direction;
	COORD position;
	int speed = 600;

	mobHandler->count = 0;

	direction = rand() % 4;
	position = (COORD){ 9,5 };

	newMob = (Mob){
		direction, direction,
		position, (COORD) { 7,3 },
		speed, 0, 0 };
	insertMobAtLast(mobHandler, newMob);
}

static void renderSampleMap(const Map* const map)
{
	for (int y = 0;y <= map->height;++y)
	{
		goto2xy(map->topLeftPosition.X, y + map->topLeftPosition.Y);
		for (int x = 0;x <= map->width;++x)
		{
			switch (map->grid[y][x]) {
			case FLAG_WALL:
				drawWallIcon();
				break;
			default:
				drawEmptyIcon();
			}
		}
	}
}

static void renderIntroHeader()
{
	textcolor(BLACK, GRAY);

	goto2xy(0, 14);
	printf("                                                                                                                                                     \n");
	printf("                                                                                                                                                     \n");
	printf("     ■■■■    ■■■■     ■■■    ■■■■     ■■■■    ■      ■        ■■■■     ■■■■         ■■       ■■■■    ■    ■     \n");
	printf("     ■     ■   ■     ■      ■     ■           ■      ■   ■■    ■        ■     ■    ■     ■       ■  ■      ■          ■   ■      \n");
	printf("     ■     ■   ■     ■      ■     ■           ■      ■   ■ ■   ■        ■     ■    ■     ■      ■    ■     ■          ■  ■       \n");
	printf("     ■■■■    ■■■■       ■      ■■■■    ■      ■   ■  ■  ■        ■■■■     ■■■■       ■■■■     ■■■■    ■■         \n");
	printf("     ■          ■    ■       ■             ■   ■      ■   ■   ■ ■        ■     ■    ■    ■      ■      ■    ■          ■  ■       \n");
	printf("     ■          ■     ■      ■             ■   ■      ■   ■    ■■        ■     ■    ■     ■    ■        ■   ■          ■   ■      \n");
	printf("     ■          ■      ■   ■■■    ■■■■     ■■■■    ■      ■        ■■■■     ■      ■   ■        ■   ■■■■    ■    ■     \n");
	printf("                                                                                                                                                     \n");
	printf("                                                                                                                                                     \n");
}

static void drawPlayGameText(IntroMenu selectedMenu)
{
	int isSelected = selectedMenu == INTRO_MENU_PLAY_GAME;

	textcolor(isSelected ? PRIMARY_COLOR : GRAY, WHITE);
	goto2xy(ACTION_LEFT_X_POS, ACTION_TOP_Y_POS);
	if (isSelected)
		printf(">  게임 시작  <");
	else
		printf("   게임 시작   ");
}

static void drawShowScoreText(IntroMenu selectedMenu)
{
	int isSelected = selectedMenu == INTRO_MENU_SHOW_SCORE;

	textcolor(isSelected ? PRIMARY_COLOR : GRAY, WHITE);
	goto2xy(ACTION_LEFT_X_POS, ACTION_TOP_Y_POS + 2);
	if (isSelected)
		printf(">  점수 보기  <");
	else
		printf("   점수 보기   ");
}

static void drawExitGameText(IntroMenu selectedMenu)
{
	int isSelected = selectedMenu == INTRO_MENU_EXIT;

	textcolor(isSelected ? PRIMARY_COLOR : GRAY, WHITE);
	goto2xy(ACTION_LEFT_X_POS, ACTION_TOP_Y_POS + 4);
	if (isSelected)
		printf(">  게임 종료  <");
	else
		printf("   게임 종료   ");
}

static COORD getSelectIconCoord(IntroMenu selectedMenu)
{
	int y, x = 40;

	switch (selectedMenu)
	{
	case INTRO_MENU_PLAY_GAME:
		y = ACTION_TOP_Y_POS;
		break;
	case INTRO_MENU_SHOW_SCORE:
		y = ACTION_TOP_Y_POS + 2;
		break;
	case INTRO_MENU_EXIT:
		y = ACTION_TOP_Y_POS + 4;
		break;
	default:
		assert(0);
	}
	return (COORD) { x, y };
}

static void renderActions(IntroMenu selectedMenu)
{
	drawPlayGameText(selectedMenu);
	drawShowScoreText(selectedMenu);
	drawExitGameText(selectedMenu);
}

static void increaseIntroMenu(IntroMenu* menu)
{
	(*menu)++;
	if (*menu > INTRO_MENU_EXIT)
		*menu = INTRO_MENU_PLAY_GAME;
}

static void decreaseIntroMenu(IntroMenu* menu)
{
	(*menu)--;
	if (*menu < INTRO_MENU_PLAY_GAME)
		*menu = INTRO_MENU_EXIT;
}

static void updateMob(
	MobHandler*		 mobHandler,
	const Map* const map
)
{
	clock_t now = clock();
	Mob* mob = &mobHandler->arrMob[0];

	if (now - mob->updatedClock > mob->moveDelay)
	{
		updateMobPosition(mob, map);
		mob->updatedClock = now;
	}
}

static int handleKbhit(IntroMenu* selectedMenu)
{
	unsigned char keybdInput;

	keybdInput = _getch();
	switch (keybdInput)
	{
	case KEYBD_UP:
		decreaseIntroMenu(selectedMenu);
		break;
	case KEYBD_DOWN:
		increaseIntroMenu(selectedMenu);
		break;
	case KEYBD_ENTER:
		return 1;
	}
	return 0;
}

IntroMenu showIntroScreen()
{
	IntroMenu selectedMenu = INTRO_MENU_PLAY_GAME;
	Map sampleMap;
	MobHandler mobHandler;
	Player samplePlayer;

	system("mode con cols=150 lines=40 | title Maze game");

	initSampleMap(&sampleMap);
	initSamplePlayer(&samplePlayer);
	initSampleMob(&mobHandler, &sampleMap);

	renderIntroHeader();
	renderSampleMap(&sampleMap);
	renderActions(selectedMenu);

	while (1)
	{
		if (_kbhit())
		{
			if (handleKbhit(&selectedMenu))
				break;

			renderActions(selectedMenu);
		}

		updateMob(&mobHandler, &sampleMap);
		renderMob(&mobHandler, &samplePlayer, &sampleMap);

		Sleep(32);
	}

	system("cls");

	return selectedMenu;
}