#include <..\psklib\GameTime.h>

#include "DunScene.h"
#include "DungreedCore.h"
#include "DunActor.h"
#include "DunRenderManager.h"
#include "DunSceneManager.h"
#include "DunCollisionManager.h"
#include "DunPlayer.h"

void DunScene::Update( )
{
	for ( auto& iter : mListOfActor )
	{
		if ( true == iter->IsCanUpdate( ) )
		{
			iter->Update( );
		}
	}
}

void DunScene::Render( )
{
	DunRenderManager::Instance( ).Render( );
}

void DunScene::Collision( )
{
	DunCollisionManager::Instance( ).Collide( );
}

void DunScene::Release( )
{
	DunRenderManager::Instance( ).Release( );
	DunCollisionManager::Instance( ).Release( );

	auto iterBegin = mListOfActor.begin( );
	const auto& End = mListOfActor.end( );
	for ( ; iterBegin != End;)
	{
		if ( false == (*iterBegin)->IsDied( ) )
		{
			++iterBegin;
			continue;
		}

		iterBegin = mListOfActor.erase(iterBegin);
	}
}

bool DunScene::MangerLoading( )
{
	DunSceneManager::Instance( ).SetCurScene(this);
	bool bCheck = Loading( );
	DunSceneManager::Instance( ).SetCurScene(nullptr);

	if ( false == bCheck )
	{
		CRASH_PROG;
	}

	mbLoaded = true;
	return mbLoaded;
}

bool DunScene::Loading( )
{
	return true;
}

DunScene::DunScene ()
	: mbLoaded(false)
{
}

DunScene::~DunScene ()
{
}

void DunScene::PrintForDebug( )
{
	/************* FPS *************/
	std::wstring debugText;
	debugText = L"FPS : ";
	debugText.append(std::to_wstring(1.0f / GameTime::DeltaTime( )));
	TextOutW(DunRenderManager::GetBackDC( ), 500, 10, debugText.c_str( ), (int)debugText.size( ));

	/************* MOUSE POS *************/
	wchar_t text[256];
	swprintf_s(
		text, L"Mouse Pos  x : %f y : %f",
		DungreedCore::MainWindow( ).GetMousePos( ).mX,
		DungreedCore::MainWindow( ).GetMousePos( ).mY
	);
	debugText = text;
	TextOutW(DunRenderManager::GetBackDC( ), 500, 30, debugText.c_str( ), (int)debugText.size( ));

	/************* PLAYER POS *************/
	swprintf_s(
		text, L"Player Pos  x : %f y : %f",
		DunPlayer::Instance( ).GetPos( ).mX,
		DunPlayer::Instance( ).GetPos( ).mY
	);
	debugText = text;
	TextOutW(DunRenderManager::GetBackDC( ), 500, 50, debugText.c_str( ), (int)debugText.size( ));
}

void DunScene::Progress( )
{
	SceneUpdate( );
	Update( );
	Render( );
	RenderDebugInfo( );
	Collision( );
	Release( );
	DunActor::ReleaseActorMemory( );
}

bool DunScene::PushBackActorInList(DunActor* _actor)
{
	if ( nullptr == _actor )
	{
		CRASH_PROG;
		return false;
	}

	mListOfActor.push_back(_actor);

	return true;
}

void DunScene::ChanageScene( )
{
	DunRenderManager::Instance( ).ClearAllRender( );
	mListOfActor.clear( );
	DunActor::PushActorWhenSceneChanging(this);
}

void DunScene::SceneUpdate( )
{
}

void DunScene::RenderDebugInfo( )
{
}
