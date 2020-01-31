#pragma once
#include <map>
#include <string>

#include <..\psklib\Debug.h>

class DunScene;
class DungreedCore;
class DunSceneManager final
{
	friend DungreedCore;
	friend DunScene;

public:

#pragma region singleton
	static DunSceneManager& Instance( )
	{
		static DunSceneManager mSingleInstance;
		return mSingleInstance;
	}
#pragma endregion

#pragma region createscene
	template<typename Type>
	bool CreateScene(const wchar_t* _name, bool _bLoadAble = true)
	{
		DunScene* findScene = FindSceneByNameOrNull(_name);
		if ( nullptr != findScene )
		{
			CRASH_PROG;
			return false;
		}

		// DunScene* newScene = new Type( );
		Type* newScene = new Type( );

		newScene->SetName(_name);
		if ( true == _bLoadAble )
		{
			newScene->MangerLoading( );
		}

		mSceneMap.insert(std::map<std::wstring, DunScene*>::value_type(_name, newScene));

		return true;
	}
#pragma endregion

	DunScene* FindSceneByNameOrNull(const wchar_t* _name);
	bool ChanageSceneByName(const wchar_t* _name);

#pragma region getset
	DunScene* GetCurSceneOrNull( ) const
	{
		return mCurScene;
	}

	void SetCurScene(DunScene* _scene)
	{
		mCurScene = _scene;
	}

	DunScene* GetCreateSceneOrNull( ) const
	{
		return mCreateScene;
	}

	void GetCreateSceneOrNull(DunScene* _scene)
	{
		mCreateScene = _scene;
	}
#pragma endregion

private:
	DunSceneManager( );
	~DunSceneManager( );

	void Progress( );

private:
	std::map<std::wstring, DunScene*> mSceneMap;

	DunScene* mCurScene;
	DunScene* mNextScene;

	// 현재 어떤 Scene이 load중인지 알려주는 용도
	DunScene* mCreateScene;
};

