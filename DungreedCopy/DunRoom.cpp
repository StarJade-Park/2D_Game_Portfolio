#include <..\psklib\Debug.h>
#include <..\psklib\GameKeyInput.h>
#include <..\psklib\GameSoundSystem.h>
#include <..\psklib\Well512Random.h>

#include "DunRoom.h"
#include "DungreedCore.h"
#include "DunRenderManager.h"
#include "DunTransRender.h"
#include "RoomDataMap.h"
#include "DunPlayer.h"
#include "DunSprite.h"
#include "DunAniRender.h"
#include "DunMonster.h"

DunRoom::DunRoom( )
	: mRoomSize( )
	, mbWormPassageAble(false), mbClear(false)
	, mDoorColRender(nullptr), mColWallRender(nullptr), mBackGround(nullptr)/*, mBackDeco(nullptr)*/
	, mBackGroundGray(nullptr), mCursor(nullptr)
	, mCommonUseStr( )
{
	mDoorColRender = CreateRender<DunTransRender>(_order::DoorOrder);
	mDoorColRender->SetSubPivotMode(PivotDirection::LeftTop);
	mDoorColRender->mIsDebug = true;

	const auto& startIter = RoomDataMap::mMapOfCurMap.find(RoomDataMap::Start);
	mCommonUseStr = startIter->second->mDoor.mTex->GetName( );
	mDoorColRender->SetSprite(mCommonUseStr.c_str( ));
	mDoorColRender->SetSubRectSize(mDoorColRender->GetSubRectSize( ) * 50);

	ChangeColImg( );
	mColWallRender = CreateRender<DunTransRender>(_order::ColOrder);
	mColWallRender->SetSubPivotMode(PivotDirection::LeftTop);
	//mColWallRender->SetSprite(mCommonUseStr);

	SetPos({ 0.0f, 0.0f });
	//mDoorColRender->OnCameraEffect( );

	mBackGround = CreateRender<DunTransRender>(_order::ShowOrder);
	mBackGround->SetSubPivotMode(PivotDirection::LeftTop);
	ChangeShowImg( );

	mBackGroundGray = CreateRender<DunTransRender>(-999);
	mBackGroundGray->SetSubPivotMode(PivotDirection::Centor);
	mBackGroundGray->SetSprite(L"bg_gray.bmp");

	mCursor = CreateRender<DunTransRender>(100);
	mCursor->SetSubPivotMode(PivotDirection::Centor);
	mCursor->SetSprite(L"ShootingCursor2.bmp");
	mCursor->SetSubRectSize(mCursor->GetSprite( ).GetImage( ).GetSize( ) * 2.0f);
	mCursor->OffCameraEffect( );

	mDoorSealSound = GameSound::PlaySoundOrNull( );
	if ( nullptr == mDoorSealSound )
	{
		CRASH_PROG;
	}
}

DunRoom::~DunRoom( )
{
	EMPTY_STATEMENT;
}

void DunRoom::ChangeColImg()
{
	size_t cutSize = mCommonUseStr.find_last_of(L'_', mCommonUseStr.size( ));
	mCommonUseStr.replace(0, cutSize, L"col_img");
	DunPlayer::Instance( ).SetColImg(mColWallRender);
}

void DunRoom::ChangeShowImg( )
{
	size_t cutSize = mCommonUseStr.find_last_of(L'_', mCommonUseStr.size( ));
	mCommonUseStr.replace(0, cutSize, L"show_img");
	mBackGround->SetSprite(mCommonUseStr);
	mBackGround->SetSubRectSize(mBackGround->GetSprite( ).GetImage( ).GetSize( ));
}

void DunRoom::Update( )
{
	DunPlayer& player = DunPlayer::Instance( );

	if ( 0 >= player.GetCurRoom( )->mAllMonster.size( ) )
	{
		mbClear = true;
	}

	if ( true == GameKeyInput::Down(L"F7") )
	{
		SwitchClear( );
	}

	mCursor->SetSubRectPos(DungreedCore::MainWindow( ).GetMousePos( ) - Geometry::MouseVal);

	GameColor color = mDoorColRender->GetSprite( ).PosToColor(player.GetColorPos( ));

	if ( true == mbClear )
	{
		if ( GameColor::White == color || GameColor::Black == color )
		{
			player.OffAbleMoveToOtherRoom( );
		}
	}
	else
	{
		player.OnAbleMoveToOtherRoom( );
	}

	if ( GameColor::Bottom__ == color && false == player.IsCanMoveOtherRoom( ) )
	{
		ChangeRoom(RoomDoorData::DoorDir::Bottom);
	}
	else if ( GameColor::Top__ == color && false == player.IsCanMoveOtherRoom( ) )
	{
		ChangeRoom(RoomDoorData::DoorDir::Top);
	}
	else if ( GameColor::Left__ == color && false == player.IsCanMoveOtherRoom( ) )
	{
		ChangeRoom(RoomDoorData::DoorDir::Left);
	}
	else if ( GameColor::Right__ == color && false == player.IsCanMoveOtherRoom( ) )
	{
		ChangeRoom(RoomDoorData::DoorDir::Right);
	}

	mCommonUseStr = DunPlayer::Instance( ).GetCurRoom( )->mDoor.mTex->GetName( );
	mDoorColRender->ResetSpriteSize( );
	mDoorColRender->SetSprite(mCommonUseStr);
	mDoorColRender->SetSubRectSize(mDoorColRender->GetSubRectSize( ) * 50);

	ChangeColImg( );
	mColWallRender->SetSprite(mCommonUseStr);
	mColWallRender->SetSubRectSize(mColWallRender->GetSprite( ).GetImage( ).GetSize( ));

	ChangeShowImg( );
	for ( auto& iter : player.GetCurRoom( )->mAllMonster )
	{
		iter->mCurRoomColImg = mColWallRender;
		iter->mSpawnRoom = player.GetCurRoom( );
	}
	
	// TODO 봉인석 위치하게 만들기
}

void DunRoom::ChangePlayerPosByDoorDir(RoomDoorData::DoorDir _dir)
{
	DunPlayer& player = DunPlayer::Instance( );

	const GamePos& newPos = player.GetCurRoom( )->mDoor.otherRoomPos[_dir];
	player.SetPos(newPos);
}

void DunRoom::ChangeRoom(RoomDoorData::DoorDir _dir)
{
	DunPlayer& player = DunPlayer::Instance( );
	player.SetCurRoom(player.GetCurRoom( )->mOtherRoom[_dir]);
	//player.GetCurRoom( )->mAllMonster;

	switch ( _dir )
	{
	case RoomDoorData::Top:
		ChangePlayerPosByDoorDir(RoomDoorData::DoorDir::Bottom);
		break;
	case RoomDoorData::Right:
		ChangePlayerPosByDoorDir(RoomDoorData::DoorDir::Left);
		break;
	case RoomDoorData::Bottom:
		ChangePlayerPosByDoorDir(RoomDoorData::DoorDir::Top);
		break;
	case RoomDoorData::Left:
		ChangePlayerPosByDoorDir(RoomDoorData::DoorDir::Right);
		break;
	case RoomDoorData::MAX: FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	mDoorSealSound->Play(L"stoneDoor.wav", 0);
	mbClear = false;
	player.OnAbleMoveToOtherRoom( );
}
