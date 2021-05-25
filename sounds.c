#include "sounds.h"

#include <assert.h>

static const unsigned short* getSoundPath(Sounds name)
{
	switch (name)
	{
	case SOUND_HEART_BEAT:
		return TEXT(SOUND_HEART_BEAT_PATH);
	case SOUND_SIREN:
		return TEXT(SOUND_SIREN_PATH);
	case SOUND_SUCCES:
		return TEXT(SOUND_SUCCESS_PATH);
	case SOUND_ALL_CLEAR:
		return TEXT(SOUND_ALL_CLEAR_PATH);
	case SOUND_EARNING_ITEM:
		return TEXT(SOUND_EARNING_ITEM_PATH);
	case SOUND_BONE_CRUSHING:
		return TEXT(SOUND_BONE_CRUSHING_PATH);
	default:
		assert(0);
		break;
	}
	return NULL;
}

void playSound(const SoundController* const controller)
{
	PlaySound(
		getSoundPath(controller->currentSound),
		NULL, 
		controller->currentPlayMode);
}

void stopSound()
{
	PlaySound(NULL, 0, 0);
}

void setSound(
	SoundController* controller, 
	Sounds			 sound, 
	int				 playMode
)
{
	controller->currentSound = sound;
	controller->currentPlayMode = playMode;

	controller->isUpdated = 1;
}

static void reserveNextSound(
	SoundController* controller,
	clock_t targetTime,
	Sounds	sound,
	int		playMode
)
{
	controller->nextSoundTime = targetTime;

	controller->nextSound = sound;
	controller->nextPlayMode = playMode;
}

void setHeartBeatLoopSound(SoundController* controller)
{
	setSound(controller, SOUND_HEART_BEAT, PLAY_MODE_LOOP);
}

void setSirenSound(SoundController* controller)
{
	setSound(controller, SOUND_SIREN, PLAY_MODE_ASYNC);
}

void setEarningItemSound(SoundController* controller)
{
	setSound(controller, SOUND_EARNING_ITEM, PLAY_MODE_ASYNC);
	reserveNextSound(
		controller,
		clock() + SOUND_EARNING_ITEM_DURATION,
		SOUND_HEART_BEAT,
		PLAY_MODE_LOOP);
}

void setBoneCrushingSound(SoundController* controller)
{
	setSound(controller, SOUND_BONE_CRUSHING, PLAY_MODE_ASYNC);
	reserveNextSound(
		controller, 
		clock() + SOUND_BONE_CRUSHING_DURATION, 
		SOUND_HEART_BEAT, 
		PLAY_MODE_LOOP);
}

void setSuccessSound(SoundController* controller)
{
	setSound(controller, SOUND_SUCCES, PLAY_MODE_ASYNC);
}

void clearNextSound(SoundController* controller)
{
	controller->nextSound = EMPTY_NEXT_SOUND;
	controller->nextSoundTime = EMPTY_NEXT_SOUND;
	controller->nextPlayMode = EMPTY_NEXT_SOUND;
}