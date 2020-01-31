#include <..\psklib\GameFileSystem.h>
#include <..\psklib\GameTime.h>
#include <..\psklib\Geometry.h>
#include <..\psklib\GameSound.h>
#include <..\psklib\GameKeyInput.h>
#include <..\psklib\tags.h>

#include "DungreedCore.h"
#include "DunSceneManager.h"
#include "DunResourceManager.h"
#include "RoomDataMap.h"

WindowController* DungreedCore::mMainWndCtrl = nullptr;

// Load Scene
void DungreedCore::StartGame( )
{
	InitBase( );
	InitPath( );
	InitImg( );
	RoomDataMap::Init( );
	InitSound( );
	InitSprite( );
	InitScene( );
	InitKeys( );
	InitColLinks( );

	DunSceneManager::Instance( ).ChanageSceneByName(L"TEST");
}

// Loop
MSG DungreedCore::RunGame( )
{
	GameTime::Reset( ); // timer reset

	MSG msg = MSG( ); // C4701 경고 방지
	while ( 0 != WindowController::GetWndCount( ) )
	{
		if ( PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			/* Game Logic */
			ConductGame( );
		}
	}

	return msg;
}

void DungreedCore::EndGame( )
{
	GameSound::End( );
	RoomDataMap::ClearCurMap( );
}

// Run
void DungreedCore::ConductGame( )
{
	WindowController::UpdateAllWnd( );
	GameTime::Update( );
	GameSound::Update( );
	GameKeyInput::Update( );

	DunSceneManager::Instance( ).Progress( );
}
