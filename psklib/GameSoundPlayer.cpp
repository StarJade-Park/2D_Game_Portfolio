#include "GameSoundPlayer.h"
#include "GameSound.h"
#include "GameSoundClip.h"
#include "Debug.h"

bool GameSoundPlayer::ReturnToPool( )
{
	if ( GameSound::mSetOfPlayPlayers.end( ) != GameSound::mSetOfPlayPlayers.find(this) )
	{
		GameSound::mSetOfPlayPlayers.erase(this);
	}

	GameSound::mPoolOfSoundPlayers.push(this);

	return true;
}

#pragma region soundplayercallback
FMOD_RESULT __stdcall SoundPlayerCallBack(
	FMOD_CHANNELCONTROL* channelcontrol,
	FMOD_CHANNELCONTROL_TYPE controltype,
	FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype,
	void* commanddata1,
	void* commanddata2)
{
	commanddata1;
	commanddata2;

	switch ( controltype )
	{
	case FMOD_CHANNELCONTROL_CHANNEL:
#pragma region fmod_channelcontrol_channel
		switch ( callbacktype )
		{
		case FMOD_CHANNELCONTROL_CALLBACK_END:
		{
			FMOD::Channel* chPointer = ((FMOD::Channel*)channelcontrol);
			void* pSoundPlayer = nullptr;

			chPointer->getUserData(&pSoundPlayer);
			if ( nullptr == pSoundPlayer )
			{
				CRASH_PROG;
			}

			GameSoundPlayer* callPlayer = (GameSoundPlayer*)pSoundPlayer;

			if ( true == callPlayer->IsRentaled( ) )
			{
				// return FMOD_OK;
				break;
			}

			callPlayer->ReturnToPool( );

			//return FMOD_OK;
			break;
		}
		case FMOD_CHANNELCONTROL_CALLBACK_VIRTUALVOICE:
			EMPTY_STATEMENT;
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_SYNCPOINT:
			EMPTY_STATEMENT;
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_OCCLUSION:
			EMPTY_STATEMENT;
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_MAX:
			EMPTY_STATEMENT;
			break;
		case FMOD_CHANNELCONTROL_CALLBACK_FORCEINT:
			EMPTY_STATEMENT;
			break;
		default:
			EMPTY_STATEMENT;
			break;
		}
#pragma endregion
		break;
	case FMOD_CHANNELCONTROL_CHANNELGROUP:
		EMPTY_STATEMENT;
		break;
	case FMOD_CHANNELCONTROL_MAX:
		EMPTY_STATEMENT;
		break;
	case FMOD_CHANNELCONTROL_FORCEINT:
		EMPTY_STATEMENT;
		break;
	default:
		EMPTY_STATEMENT;
		break;
	}

	return FMOD_RESULT::FMOD_OK;
}
#pragma endregion

bool GameSoundPlayer::Play(const wchar_t* _soundName, int _loopCount /*= 0*/)
{
	GameSoundClip* fClip = GameSound::FindSoundOrNull(_soundName);
	if ( nullptr == fClip )
	{
		CRASH_PROG;
		return false;
	}

	GameSound::mMainSoundSystem->playSound(fClip->mSound, nullptr, false, &mChannel);
	if ( nullptr == mChannel )
	{
		CRASH_PROG;
		return false;
	}

	mChannel->setCallback(SoundPlayerCallBack); // function pointer
	mChannel->setUserData(this);
	mChannel->setMode(FMOD_LOOP_NORMAL /*| FMOD_2D*/); // bit flag
	mChannel->setLoopCount(_loopCount);

	if ( GameSound::mSetOfPlayPlayers.end( ) != GameSound::mSetOfPlayPlayers.find(this) )
	{
		GameSound::mSetOfPlayPlayers.insert(this);
	}

	return true;
}

void GameSoundPlayer::Stop( )
{
	if ( nullptr == mChannel )
	{
		CRASH_PROG;
		return;
	}

	mChannel->stop( );
	mChannel = nullptr;
}
