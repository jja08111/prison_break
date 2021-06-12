#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include <windows.h> 
#include <time.h>
#pragma comment (lib, "winmm.lib")

#define SOUND_INTRO_PATH			"assets\\sounds\\intro.wav"
#define SOUND_HEART_BEAT_PATH		"assets\\sounds\\heart_beat.wav"
#define SOUND_SUCCESS_PATH			"assets\\sounds\\success.wav"
#define SOUND_SIREN_PATH			"assets\\sounds\\siren.wav"
#define SOUND_ALL_CLEAR_PATH		"assets\\sounds\\all_clear.wav"
#define SOUND_EARNING_ITEM_PATH		"assets\\sounds\\earning_item.wav"
#define SOUND_BONE_CRUSHING_PATH	"assets\\sounds\\bone_crushing.wav"
#define SOUND_BUTTON_PATH			"assets\\sounds\\button.wav"
#define SOUND_TRANSITION_PATH		"assets\\sounds\\transition.wav"

#define SOUND_EARNING_ITEM_DURATION		1000
#define SOUND_BONE_CRUSHING_DURATION	1000

#define PLAY_MODE_SYNC		SND_FILENAME | SND_SYNC
#define PLAY_MODE_ASYNC		SND_FILENAME | SND_ASYNC
#define PLAY_MODE_LOOP		SND_FILENAME | SND_ASYNC | SND_LOOP

#define EMPTY_NEXT_SOUND	-1

typedef enum {
	SOUND_HEART_BEAT,
	SOUND_SIREN,
	SOUND_SUCCES,
	SOUND_ALL_CLEAR,	
	SOUND_EARNING_ITEM,	
	SOUND_BONE_CRUSHING,
	SOUND_BUTTON,
	SOUND_TRANSITION,
	SOUND_INTRO
} Sounds;

typedef struct _SoundController {
	int isUpdated;
	Sounds currentSound;
	DWORD currentPlayMode; // [PLAY_MODE_SYNC] or [PLAY_MODE_ASYNC] or [PLAY_MODE_LOOP]

	Sounds nextSound;
	clock_t nextSoundTime;
	DWORD nextPlayMode;
} SoundController;

void playIntroSound();

void playTransitionSound();

void playButtonSound();

void playSound(const SoundController* const controller);

void setSound(
	SoundController* controller,
	Sounds			 sound,
	int				 playMode
);
void setHeartBeatLoopSound(SoundController* controller);
void setSirenSound(SoundController* controller);
void setEarningItemSound(SoundController* controller);
void setBoneCrushingSound(SoundController* controller);
void setSuccessSound(SoundController* controller);
void setAllClearSound(SoundController* controller);

void stopSound();

void clearNextSound(SoundController* controller);

#endif