#include <..\psklib\GameFileSystem.h>
#include <..\psklib\GameTime.h>
#include <..\psklib\Geometry.h>
#include <..\psklib\GameSound.h>
#include <..\psklib\GameKeyInput.h>
#include <..\psklib\tags.h>

#include "DungreedCore.h"
#include "DunResourceManager.h"
#include "DunCollisionManager.h"
#include "DunPlayer.h"
#include "RoomDataMap.h"
#include "DunImage.h"

#include "DungreedTitle.h"
#include "DungreedStage_Town.h"
#include "DungreedStage_01.h"
#include "DungreedBoss_01.h"
#include "DungreedEnd.h"
#include "DunTestStage.h"

void DungreedCore::InitBase( )
{
	mMainWndCtrl = WindowController::CreateNewWindowOrNull(L"Dungreed");
	if ( nullptr == mMainWndCtrl )
	{
		CRASH_PROG;
	}

	mMainWndCtrl->SetWndSize(def::__tag::width, def::__tag::height);

	GameSound::Init( );
	GameDirectory::Init( ); // set rootpath to BIN
}

void DungreedCore::InitPath( )
{
	// - 예시
	//GameDirectory::InsertPathMap(
	//	L"Charcter",
	//	GamePath::Join(GameDirectory::GetRootPath( ), L"Sprite\\Charcter").c_str( )
	//);

	// - img
	GameDirectory::InsertPathMap(L"img", GamePath::Join(GameDirectory::GetRootPath( ), L"img").c_str( ));
	GameDirectory::InsertPathMap(L"char", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\char").c_str( ));
	GameDirectory::InsertPathMap(L"fx", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\fx").c_str( ));
	GameDirectory::InsertPathMap(L"room_info", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\room_info").c_str( ));
	GameDirectory::InsertPathMap(L"col_img", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\col_img").c_str( ));
	GameDirectory::InsertPathMap(L"show_img", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\show_img").c_str( ));
	GameDirectory::InsertPathMap(L"weapon", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\weapon").c_str( ));
	GameDirectory::InsertPathMap(L"weapon_fx", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\weapon_fx").c_str( ));
	GameDirectory::InsertPathMap(L"bg", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\bg").c_str( ));
	GameDirectory::InsertPathMap(L"Seal", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\Seal").c_str( ));
	GameDirectory::InsertPathMap(L"skel", GamePath::Join(GameDirectory::GetRootPath( ), L"img\\skel").c_str( ));

	// - sound
	GameDirectory::InsertPathMap(L"sound", GamePath::Join(GameDirectory::GetRootPath( ), L"sound").c_str( ));
}

void DungreedCore::InitImg( )
{
	// char
	GameDirectoryInfo dir = GameDirectory::FindPathToDirOrNull(L"char");
	const std::vector<std::wstring>& charFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : charFiles )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	// fx
	dir = GameDirectory::FindPathToDirOrNull(L"fx");
	const std::vector<std::wstring>& fxFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : fxFiles )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"col_img");
	const std::vector<std::wstring>& colImgFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : colImgFiles )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"show_img");
	const std::vector<std::wstring>& showImgFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : showImgFiles )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"weapon");
	const std::vector<std::wstring>& weaponFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : weaponFiles )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"weapon_fx");
	const std::vector<std::wstring>& w_fxFile = dir.GetAllFilesToStr( );
	for ( auto& iter : w_fxFile )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"bg");
	const std::vector<std::wstring>& bgFile = dir.GetAllFilesToStr( );
	for ( auto& iter : bgFile )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"Seal");
	const std::vector<std::wstring>& sealFile = dir.GetAllFilesToStr( );
	for ( auto& iter : sealFile )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}

	dir = GameDirectory::FindPathToDirOrNull(L"skel");
	const std::vector<std::wstring>& skelFile = dir.GetAllFilesToStr( );
	for ( auto& iter : skelFile )
	{
		DunResourceManager::LoadImageOrNull(iter.c_str( ));
	}
}

void DungreedCore::InitSound( )
{
	GameDirectoryInfo dir = GameDirectory::FindPathToDirOrNull(L"sound");

	const std::vector<std::wstring>& fxFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : fxFiles )
	{
		GameSound::LoadSoundOrNull(iter.c_str( ));
	}
}

void DungreedCore::InitSprite( )
{
	// - 예시
	//GameResourceManager::CreateSprite (L"Player.bmp", 5, 38);

	// 맵
	std::vector<DunImage*>& vectorOfAllRoomImg = RoomDataMap::GetAllImg( );
	for ( auto& iter : vectorOfAllRoomImg )
	{
		DunResourceManager::CreateSprite(iter->GetName( ).c_str( ), 1, 1);
	}

	GameDirectoryInfo dir = GameDirectory::FindPathToDirOrNull(L"col_img");
	const std::vector<std::wstring>& colImgFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : colImgFiles )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 1, 1);
	}

	dir = GameDirectory::FindPathToDirOrNull(L"show_img");
	const std::vector<std::wstring>& showImgFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : showImgFiles )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 1, 1);
	}


	dir = GameDirectory::FindPathToDirOrNull(L"weapon");
	const std::vector<std::wstring>& w_fxFile = dir.GetAllFilesToStr( );
	for ( auto& iter : w_fxFile )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 1, 1);
	}

	dir = GameDirectory::FindPathToDirOrNull(L"weapon_fx");
	const std::vector<std::wstring>& weaponFiles = dir.GetAllFilesToStr( );
	for ( auto& iter : weaponFiles )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 1, 1);
	}

	dir = GameDirectory::FindPathToDirOrNull(L"bg");
	const std::vector<std::wstring>& bgFile = dir.GetAllFilesToStr( );
	for ( auto& iter : bgFile )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 1, 1);
	}

	dir = GameDirectory::FindPathToDirOrNull(L"Seal");
	const std::vector<std::wstring>& sealFile = dir.GetAllFilesToStr( );
	for ( auto& iter : sealFile )
	{
		DunResourceManager::CreateSprite(GamePath::BaseName(iter.c_str( )).c_str( ), 8, 1);
	}

	// 캐릭터
	// Die, Idle, Jump, Run, Walk, Attack, DoubleJump, MAX
	DunResourceManager::CreateSprite(L"L_Die.bmp", DunPlayer::_AniIndex::DieEnd, 1);
	DunResourceManager::CreateSprite(L"R_Die.bmp", DunPlayer::_AniIndex::DieEnd, 1);

	DunResourceManager::CreateSprite(L"L_Idle.bmp", DunPlayer::_AniIndex::IdleEnd, 1);
	DunResourceManager::CreateSprite(L"R_Idle.bmp", DunPlayer::_AniIndex::IdleEnd, 1);

	DunResourceManager::CreateSprite(L"L_Jump.bmp", DunPlayer::_AniIndex::JumpEnd, 1);
	DunResourceManager::CreateSprite(L"R_Jump.bmp", DunPlayer::_AniIndex::JumpEnd, 1);

	DunResourceManager::CreateSprite(L"L_Attack.bmp", DunPlayer::_AniIndex::JumpEnd, 1);
	DunResourceManager::CreateSprite(L"R_Attack.bmp", DunPlayer::_AniIndex::JumpEnd, 1);

	DunResourceManager::CreateSprite(L"L_Run.bmp", DunPlayer::_AniIndex::RunEnd, 1);
	DunResourceManager::CreateSprite(L"R_Run.bmp", DunPlayer::_AniIndex::RunEnd, 1);

	DunResourceManager::CreateSprite(L"L_Walk.bmp", DunPlayer::_AniIndex::WalkEnd, 1);
	DunResourceManager::CreateSprite(L"R_Walk.bmp", DunPlayer::_AniIndex::WalkEnd, 1);

	// fx
	DunResourceManager::CreateSprite(L"Idle_Run_Dust.bmp", 1, 1);
	DunResourceManager::CreateSprite(L"L_Run_Dust.bmp", DunPlayer::_AniIndex::DustEnd, 1);
	DunResourceManager::CreateSprite(L"R_Run_Dust.bmp", DunPlayer::_AniIndex::DustEnd, 1);

	DunResourceManager::CreateSprite(L"Char_Hand.bmp", 1, 1);

	DunResourceManager::CreateSprite(L"L_DoubleJump.bmp", DunPlayer::_AniIndex::JumpEnd, 1);
	DunResourceManager::CreateSprite(L"R_DoubleJump.bmp", DunPlayer::_AniIndex::JumpEnd, 1);

	// skel
	DunResourceManager::CreateSprite(L"L_SkelAttack.bmp", 12, 1);
	DunResourceManager::CreateSprite(L"L_SkelIdle.bmp", 6, 1);
	DunResourceManager::CreateSprite(L"L_SkelMove.bmp", 6, 1);
	DunResourceManager::CreateSprite(L"R_SkelAttack.bmp", 12, 1);
	DunResourceManager::CreateSprite(L"R_SkelIdle.bmp", 6, 1);
	DunResourceManager::CreateSprite(L"R_SkelMove.bmp", 6, 1);

}

void DungreedCore::InitScene( )
{
	DunSceneManager::Instance( ).CreateScene<DungreedTitle>(L"Title");
	DunSceneManager::Instance( ).CreateScene<DungreedStage_Town>(L"Town");
	DunSceneManager::Instance( ).CreateScene<DungreedStage_Town>(L"Stage_01");
	DunSceneManager::Instance( ).CreateScene<DungreedStage_Town>(L"Boss_01");
	DunSceneManager::Instance( ).CreateScene<DungreedEnd>(L"End");

	DunSceneManager::Instance( ).CreateScene<DunTestStage>(L"TEST");

	// 플레이어만 예외적으로 처리하였음
	DunPlayer::Instance( ).InsertActorToScene(L"Town", L"Stage_01", L"Boss_01", L"End", L"TEST");
}

void DungreedCore::InitKeys( )
{
	//GameKeyInput::CreateKey(L"", );
	GameKeyInput::CreateKey(L"LMB", VK_LBUTTON);
	GameKeyInput::CreateKey(L"RMB", VK_RBUTTON);
	GameKeyInput::CreateKey(L"Left", 'A');
	GameKeyInput::CreateKey(L"Up", 'W');
	GameKeyInput::CreateKey(L"Right", 'D');
	GameKeyInput::CreateKey(L"Down", 'S');
	GameKeyInput::CreateKey(L"Tab", VK_TAB);
	GameKeyInput::CreateKey(L"Debug", VK_F6);
	GameKeyInput::CreateKey(L"Space", VK_SPACE);

	GameKeyInput::CreateKey(L"F7", VK_F7);
	GameKeyInput::CreateKey(L"F8", VK_F8);
}

void DungreedCore::InitColLinks( )
{
	DunCollisionManager::Instance( ).SetLink(L"Player_col", L"mon_sword");
	DunCollisionManager::Instance( ).SetLink(L"Monster", L"player_sword");
}
