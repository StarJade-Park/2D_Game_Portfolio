#include "DunSceneManager.h"
#include "DunScene.h"


DunScene* DunSceneManager::FindSceneByNameOrNull(const wchar_t * _name)
{
	const auto& findIter = mSceneMap.find(_name);

	if ( mSceneMap.end( ) == findIter )
	{
		return nullptr;
	}

	return findIter->second;
}

bool DunSceneManager::ChanageSceneByName(const wchar_t * _name)
{
	mCurScene = FindSceneByNameOrNull(_name);
	if ( nullptr == mCurScene )
	{
		CRASH_PROG;
		false;
	}

	return true;
}

DunSceneManager::DunSceneManager( )
	: mCurScene(nullptr)
	, mNextScene(nullptr)
	, mCreateScene(nullptr)
{
}

DunSceneManager::~DunSceneManager( )
{
	for ( auto& iter : mSceneMap )
	{
		if ( nullptr != iter.second )
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}

void DunSceneManager::Progress( )
{
	if ( nullptr != mNextScene )
	{
		mCurScene = mNextScene;

		if ( false == mCurScene->IsLoaded( ) )
		{
			mCurScene->MangerLoading( );
		}

		// 로딩이 끝나도 상관없는 동작
		mCurScene->ChanageScene( );

		mNextScene = nullptr;
	}

	if ( nullptr != mCurScene )
	{
		mCurScene->Progress( );
	}
	else
	{
		CRASH_PROG;
	}
}
