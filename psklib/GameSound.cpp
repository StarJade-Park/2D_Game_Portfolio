#include <vector>
#include <atlstr.h> // wchar_t -> char

#include "GameSound.h"
#include "GameSoundPlayer.h"
#include "GameSoundClip.h"
#include "GamePath.h"
#include "Debug.h"

#pragma region static_member
FMOD::System*							GameSound::mMainSoundSystem = nullptr;
std::map<std::wstring, GameSoundClip*>	GameSound::mMapOfClips;
// - pool에 있으면 상태가 재생 중이 아님
std::stack<GameSoundPlayer*>			GameSound::mPoolOfSoundPlayers;
// - rental 중인 player set, 재생 중임
std::set<GameSoundPlayer*>				GameSound::mSetOfPlayPlayers;
#pragma endregion

bool GameSound::Init(int _count/* = __tag::CountMax*/)
{
	FMOD_RESULT eResult = FMOD::System_Create(&mMainSoundSystem);
	if ( nullptr == mMainSoundSystem || FMOD_RESULT::FMOD_OK != eResult )
	{
		CRASH_PROG;
		return false;
	}

	eResult = mMainSoundSystem->init(32, FMOD_DEFAULT, nullptr);
	if ( FMOD_RESULT::FMOD_OK != eResult )
	{
		CRASH_PROG;
		return false;
	}

	for ( int i = 0; i < _count; ++i )
	{
		mPoolOfSoundPlayers.push(new GameSoundPlayer( ));
	}

	return true;
}

void GameSound::Update( )
{
	if ( nullptr != mMainSoundSystem )
	{
		mMainSoundSystem->update( );
	}
}

void GameSound::End( )
{
	for ( auto& iter : mMapOfClips )
	{
		delete iter.second;
		iter.second = nullptr;
	}

	while ( 0 < mPoolOfSoundPlayers.size( ) )
	{
		GameSoundPlayer* soundPlayer = mPoolOfSoundPlayers.top( );
		delete soundPlayer;
		soundPlayer = nullptr;
		mPoolOfSoundPlayers.pop( );
	}

	for ( auto& iter : mSetOfPlayPlayers )
	{
		delete iter;
	}

	mMainSoundSystem->release( );
}

GameSoundClip* GameSound::LoadSoundOrNull(const wchar_t* _path)
{
	std::wstring key = GamePath::BaseName(_path);

	return LoadSoundOrNull(key.c_str( ), _path);
}

GameSoundClip* GameSound::LoadSoundOrNull(const wchar_t* _name, const wchar_t* _path)
{
	if ( nullptr != FindSoundOrNull(_name) )
	{
		CRASH_PROG;
		return nullptr;
	}

	FMOD::Sound* newSound = nullptr;
	//std::string str = (LPSTR)CW2A(_path, CP_UTF8);
	FMOD_RESULT eResult = \
		mMainSoundSystem->createSound(CW2A(_path, CP_UTF8), FMOD_DEFAULT, nullptr, &newSound);
	if ( nullptr == newSound || FMOD_RESULT::FMOD_OK != eResult )
	{
		CRASH_PROG;
		return nullptr;
	}

	GameSoundClip* newSoundClip = new GameSoundClip( );
	newSoundClip->mSound = newSound;
	mMapOfClips.insert(
		std::map<std::wstring, GameSoundClip*>::value_type(_name, newSoundClip)
	);

	return newSoundClip;
}

void GameSound::PlaySoundByLoopCount(const wchar_t* _name, int _loopCount/* = 0*/)
{
	if ( 0 >= mPoolOfSoundPlayers.size( ) )
	{
		OutputDebugStringW(L"[GameSound] Sound Pool Size : 0");
		return;
	}

	GameSoundPlayer* player = mPoolOfSoundPlayers.top( );
	mPoolOfSoundPlayers.pop( );
	player->Play(_name, _loopCount);
}

GameSoundPlayer* GameSound::PlaySoundOrNull( )
{
	if ( 0 >= mPoolOfSoundPlayers.size( ) )
	{
		OutputDebugStringW(L"[GameSound] Sound Pool Size : 0, return nullptr");
		return nullptr;
	}

	GameSoundPlayer* rentalPlayer = mPoolOfSoundPlayers.top( );
	mPoolOfSoundPlayers.pop( );
	rentalPlayer->mbRental = true;
	mSetOfPlayPlayers.insert(rentalPlayer);

	return rentalPlayer;
}

void GameSound::StopAllSoundPlayer( )
{
	if ( 0 >= mSetOfPlayPlayers.size( ) )
	{
		OutputDebugStringW(L"[GameSound] sound player : 0");
		return;
	}

	std::vector<GameSoundPlayer*> vectorOfSound = std::vector<GameSoundPlayer*>( );
	vectorOfSound.reserve(mSetOfPlayPlayers.size( ));

	for ( auto& iter : mSetOfPlayPlayers )
	{
		if ( false == iter->IsRentaled( ) )
		{
			vectorOfSound.push_back(iter);
		}
	}

	for ( auto& iter : vectorOfSound )
	{
		iter->Stop( );
	}

	mSetOfPlayPlayers.clear( );
}

GameSoundClip* GameSound::FindSoundOrNull(const wchar_t* _name)
{
	const auto& findIter = mMapOfClips.find(_name);
	if ( mMapOfClips.end( ) == findIter )
	{
		return nullptr;
	}

	return findIter->second;
}
