#ifndef __INTRO_H__
#define __INTRO_H__

typedef enum {
	INTRO_MENU_PLAY_GAME,
	INTRO_MENU_SHOW_SCORE,
	INTRO_MENU_EXIT
} IntroMenu;

// ��Ʈ�� ȭ���� �����ְ� ������ ������ �޴��� ��ȯ�Ѵ�.
IntroMenu showIntroScreen();

#endif