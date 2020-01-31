#pragma once
#include <string>
#include <vector>
#include <map>

#include "tags.h"
#include "Debug.h"
class GameKeyInput
{
private:
#pragma region KeyDestroyer
	class KeyDestroyer
	{
	public:
		KeyDestroyer () = default;
		~KeyDestroyer ()
		{
			GameKeyInput::EndInput ();
		}
	};
	static KeyDestroyer mDestructor;
	friend KeyDestroyer;
#pragma endregion

#pragma region gamekey_class
	class GameKey
	{
		friend GameKeyInput;
	public:
		bool mbUp;
		bool mbAFK; // - Away from keyborad(UpAway), not press
		bool mbDown;
		bool mbPress;
		std::vector<int> mKeyArray;

	public:
		bool IsInputKey ();
		void Update ();

	private:
		GameKey ()
			: mbUp (false), mbAFK (true), mbDown (false), mbPress (false)
		{
			EMPTY_STATEMENT;
		}

		~GameKey () = default;
	};
#pragma endregion

public:
	GameKeyInput () = default;
	~GameKeyInput () = default;

	static bool Down (const wchar_t* _keyName);
	static bool AKF (const wchar_t* _keyName);
	static bool Press (const wchar_t* _keyName);
	static bool Up (const wchar_t* _keyName);
	
	static void Update ();

private:
	static void EndInput ();
	static GameKey* FindKeyOrNull (const wchar_t* _name);

#pragma region createkey
public:
	template<typename ...Rest>
	static void CreateKey (const wchar_t* _keyName, Rest ..._Args)
	{
		newKey = FindKeyOrNull (_keyName);

		if (nullptr != newKey)
		{
			CRASH_PROG;
			return;
		}

		newKey = new GameKey ();
		newKey->mKeyArray.reserve (sizeof...(_Args));
		PushBackKey (_Args...);

		mAllKeyMap.insert (std::map<std::wstring, GameKey*>::value_type (_keyName, newKey));
	}

private:
	template<typename ...Rest>
	static void PushBackKey (int _key, Rest ..._Args)
	{
		newKey->mKeyArray.push_back (_key);
		PushBackKey (_Args...);
	}

	static void PushBackKey ()
	{
	}
#pragma endregion

private:
	static std::map<std::wstring, GameKey*> mAllKeyMap;
	static GameKey* newKey;
};

