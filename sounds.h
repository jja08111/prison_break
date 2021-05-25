#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include <windows.h> 
#include <time.h>
#pragma comment (lib, "winmm.lib")

#define SOUND_INTRO_PATH			"assets\\intro.wav"
#define SOUND_HEART_BEAT_PATH		"assets\\heart_beat.wav"
#define SOUND_SUCCESS_PATH			"assets\\success.wav"
#define SOUND_SIREN_PATH			"assets\\siren.wav"
#define SOUND_ALL_CLEAR_PATH		"assets\\background_track.wav"
#define SOUND_EARNING_ITEM_PATH		"assets\\earning_item.wav"
#define SOUND_BONE_CRUSHING_PATH	"assets\\bone_crushing.wav"

#define SOUND_EARNING_ITEM_DURATION		1000
#define SOUND_BONE_CRUSHING_DURATION	1000

#define PLAY_MODE_ASYNC		SND_FILENAME | SND_ASYNC
#define PLAY_MODE_LOOP		SND_FILENAME | SND_ASYNC | SND_LOOP

#define EMPTY_NEXT_SOUND	-1

typedef enum {
	SOUND_HEART_BEAT,
	SOUND_SIREN,
	SOUND_SUCCES,
	SOUND_ALL_CLEAR,	
	SOUND_EARNING_ITEM,	
	SOUND_BONE_CRUSHING
} Sounds;

typedef struct _SoundController {
	int isUpdated;
	Sounds currentSound;
	DWORD currentPlayMode; // [PLAY_MODE_ASYNC] or [PLAY_MODE_LOOP]

	Sounds nextSound;
	clock_t nextSoundTime;
	DWORD nextPlayMode;
} SoundController;

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

void stopSound();

void clearNextSound(SoundController* controller);

#endif