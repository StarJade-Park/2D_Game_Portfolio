#pragma once
#include <map>
#include <set>
#include <stack>
#include <string>

#include <..\FMOD\inc\fmod.hpp>

#include "SoundDef.h"
#include "tags.h"

class GameSoundClip;
class GameSoundPlayer;
// - Static class
class GameSound
{
	friend GameSoundPlayer;
#pragma region enums
private:
	enum __tag
	{
		CountMax = 128,
	};
#pragma endregion
public:
	// - _count : 동시 재생 가능 수
	static bool Init(int _count = __tag::CountMax);
	static void Update( );
	static void End( );

	static GameSoundClip* LoadSoundOrNull(const wchar_t* _path);
	static GameSoundClip* LoadSoundOrNull(const wchar_t* _name, const wchar_t* _path);

	// - 재생하고 알아서 처리
	// - loop count : 반복 횟수, 0은 1회
	static void PlaySoundByLoopCount(const wchar_t* _name, int _loopCount = 0);

	// - SoundPlayer의 pointer를 가지려면 쓸 것
	static GameSoundPlayer* PlaySoundOrNull( );

	static void StopAllSoundPlayer( );

private:
	GameSound( ) = delete;
	~GameSound( ) = delete;

	static GameSoundClip* FindSoundOrNull(const wchar_t* _name);

private: // pool 관리 방식
	/*
		- pool을 만드는 이유
		- create, delete의 부담이 커서 한 번에 만들어두고 프로그램 종료시 삭제하기 위함
	*/

	static FMOD::System* mMainSoundSystem;
	static std::map<std::wstring, GameSoundClip*> mMapOfClips;

	// - pool에 있으면 상태가 재생 중이 아님
	static std::stack<GameSoundPlayer*> mPoolOfSoundPlayers; 
	// - rental 중인 player set, 재생 중임
	static std::set<GameSoundPlayer*> mSetOfPlayPlayers;
};

