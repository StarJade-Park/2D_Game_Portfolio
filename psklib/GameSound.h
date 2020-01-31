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
	// - _count : ���� ��� ���� ��
	static bool Init(int _count = __tag::CountMax);
	static void Update( );
	static void End( );

	static GameSoundClip* LoadSoundOrNull(const wchar_t* _path);
	static GameSoundClip* LoadSoundOrNull(const wchar_t* _name, const wchar_t* _path);

	// - ����ϰ� �˾Ƽ� ó��
	// - loop count : �ݺ� Ƚ��, 0�� 1ȸ
	static void PlaySoundByLoopCount(const wchar_t* _name, int _loopCount = 0);

	// - SoundPlayer�� pointer�� �������� �� ��
	static GameSoundPlayer* PlaySoundOrNull( );

	static void StopAllSoundPlayer( );

private:
	GameSound( ) = delete;
	~GameSound( ) = delete;

	static GameSoundClip* FindSoundOrNull(const wchar_t* _name);

private: // pool ���� ���
	/*
		- pool�� ����� ����
		- create, delete�� �δ��� Ŀ�� �� ���� �����ΰ� ���α׷� ����� �����ϱ� ����
	*/

	static FMOD::System* mMainSoundSystem;
	static std::map<std::wstring, GameSoundClip*> mMapOfClips;

	// - pool�� ������ ���°� ��� ���� �ƴ�
	static std::stack<GameSoundPlayer*> mPoolOfSoundPlayers; 
	// - rental ���� player set, ��� ����
	static std::set<GameSoundPlayer*> mSetOfPlayPlayers;
};

