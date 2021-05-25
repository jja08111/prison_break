#ifndef __INTRO_H__
#define __INTRO_H__

typedef enum {
	INTRO_MENU_PLAY_GAME,
	INTRO_MENU_SHOW_SCORE,
	INTRO_MENU_EXIT
} IntroMenu;

// 인트로 화면을 보여주고 유저가 선택한 메뉴를 반환한다.
IntroMenu showIntroScreen();

#endif