#pragma once
#include <..\FMOD\inc\fmod.hpp>

#include "SoundDef.h"
#include "tags.h"

class GameSound;
class GameSoundPlayer;
class GameSoundClip
{
	friend GameSound;
	friend GameSoundPlayer;
public:
	// - ms 단위 길이 반환
	unsigned int GetSoundLen( ) const
	{
		unsigned int Value = 0;
		mSound->getLength(&Value, FMOD_TIMEUNIT_MS);

		return Value;
	}

private:
	GameSoundClip( )
		: mSound(nullptr)
	{
		EMPTY_STATEMENT;
	}

	~GameSoundClip( )
	{
		mSound->release( );
		mSound = nullptr;
	}

private:
	FMOD::Sound* mSound;
};

