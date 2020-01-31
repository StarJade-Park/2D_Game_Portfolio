#pragma once
#include <..\FMOD\inc\fmod.hpp>

#include "SoundDef.h"
#include "tags.h"

class GameSound;
class GameSoundClip;
class GameSoundPlayer
{
	friend GameSound;
public:
	bool ReturnToPool( );
	bool Play(const wchar_t* _soundName, int _loopCount = 1);
	void Stop( );

	bool IsRentaled( ) const
	{
		return mbRental;
	}

private:
	GameSoundPlayer( )
		: mSoundClip(nullptr)
		, mChannel(nullptr)
		, mbRental(false)
	{
		EMPTY_STATEMENT;
	}

	~GameSoundPlayer( ) = default;

private:
	GameSoundClip* mSoundClip;
	FMOD::Channel* mChannel;
	bool mbRental;
};

