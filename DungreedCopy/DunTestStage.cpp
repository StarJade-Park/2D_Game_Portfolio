#include <random>

#include <..\psklib\GameFileSystem.h>
#include <..\psklib\GameSoundSystem.h>
#include <..\psklib\GameKeyInput.h>

#include "DunTestStage.h"
#include "DungreedCore.h"
#include "DunSceneManager.h"
#include "DunResourceManager.h"
#include "DunRenderManager.h"
#include "DunPlayer.h"
#include "DunRoom.h"
#include "RoomDataMap.h"
#include "DunMonster.h"

#include "DunSprite.h"
#include "DunTransRender.h"

int DunTestStage::MaxCounterRoom = 15;

DunTestStage::DunTestStage( )
	: mBgm(nullptr), mCurRoom(nullptr), mDunRoom(nullptr)
{
	EMPTY_STATEMENT;
}

DunTestStage::~DunTestStage( )
{
	EMPTY_STATEMENT;
}

bool DunTestStage::Loading( )
{
	mBgm = GameSound::PlaySoundOrNull( );
	if ( nullptr == mBgm )
	{
		CRASH_PROG;
		return false;
	}
	mBgm->Play(L"1.JailField.wav", INT_MAX);

	LoadRoomData( );
	DunPlayer::Instance( ).SetCurRoom(mCurRoom);

	mDunRoom = DunActor::CreateActor<DunRoom>(L"TEST_Stage", true);
	mDunRoom->InsertActorToScene(L"TEST");

	DunPlayer::Instance( ).SetPos(GamePos(100.f, 100.f));

	return true;
}

void DunTestStage::SceneUpdate( )
{
	mCurRoom = DunPlayer::Instance( ).GetCurRoom( );
	if ( nullptr == mCurRoom )
	{
		CRASH_PROG;
	}

	mDunRoom->GetRenderForColDoor( ).SetSubRectPos(
		mDunRoom->GetRenderForColDoor( ).GetActorPos( )
	);

	if ( true == GameKeyInput::Down(L"Debug"))
	{
		DunRenderManager::SwitchDebugRender( );
	}

}

void DunTestStage::RenderDebugInfo( )
{
	PrintForDebug( );

	std::wstring debugText = GetName( );
	debugText += L", " + std::wstring(mDunRoom->GetRenderForColDoor( ).GetSprite( ).GetImage( ).GetName( ));
	TextOutW(DunRenderManager::GetBackDC( ), 10, 10, debugText.c_str( ), (int)debugText.size( ));
	
	wchar_t text[256];
	swprintf_s(
		text, L"Map Pos  x : %d, y : %d | Camera Pos : %d, %d",
		mCurRoom->mMapKey.X,
		mCurRoom->mMapKey.Y,
		DunSceneManager::Instance( ).GetCurSceneOrNull( )->GetCameraPos( ).XToInt(),
		DunSceneManager::Instance( ).GetCurSceneOrNull( )->GetCameraPos( ).YToInt()
	);
	
	debugText = text;
	TextOutW(DunRenderManager::GetBackDC( ), 10, 30, debugText.c_str( ), (int)debugText.size( ));

	swprintf_s(
		text, L"Mouse Dir(Angle) %f",
		DunPlayer::Instance( ).mMouseDir.DirToAngle( )
	);
	debugText = text;
	TextOutW(DunRenderManager::GetBackDC( ), 10, 50, debugText.c_str( ), (int)debugText.size( ));

	debugText = L"Open door info ";
	for ( GamePos i : mCurRoom->mDoor.otherRoomPos )
	{
		i = i * 0.02f;
		debugText += std::to_wstring((int)i.mX) + L", " + std::to_wstring((int)i.mY) + L" | ";
	}
	TextOutW(DunRenderManager::GetBackDC( ), 10, 70, debugText.c_str( ), (int)debugText.size( ));

	debugText = L"room size "
		+ std::to_wstring(mCurRoom->mDoor.mTex->GetSize( ).mX) + L", "
		+ std::to_wstring(mCurRoom->mDoor.mTex->GetSize( ).mY);
	TextOutW(DunRenderManager::GetBackDC( ), 500, 70, debugText.c_str( ), (int)debugText.size( ));
	
	debugText = L"Clear? ";
	if ( true == mDunRoom->IsCleared( ) )
	{
		debugText += L"True";
	}
	else
	{
		debugText += L"False";
	}
	TextOutW(DunRenderManager::GetBackDC( ), 500, 90, debugText.c_str( ), (int)debugText.size( ));

	debugText = L"monster counter: "
		+ std::to_wstring(DunPlayer::Instance( ).GetCurRoom( )->mAllMonster.size( ));
	TextOutW(DunRenderManager::GetBackDC( ), 500, 110, debugText.c_str( ), (int)debugText.size( ));
}

void DunTestStage::LoadRoomData( )
{
	mCurRoom = RoomDataMap::CreateRandomDun(MaxCounterRoom);
}
