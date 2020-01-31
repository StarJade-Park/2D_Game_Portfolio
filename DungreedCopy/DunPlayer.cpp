#include <..\psklib\GameTime.h>
#include <..\psklib\GameKeyInput.h>
#include <..\psklib\GameSoundSystem.h>
#include <..\psklib\Well512Random.h>

#include "DunPlayer.h"
#include "DungreedCore.h"
#include "DunSceneManager.h"
#include "DunTransRender.h"
#include "DunRoom.h"
#include "DunSprite.h"
#include "RoomData.h"
#include "DunRectCollider.h"
#include "DunMonster.h"

std::wstring DunPlayer::mAniNames[static_cast<size_t>(__PlayerState::MAX)] = \
{ L"Die", L"Idle", L"Jump", L"Run", L"Walk", L"Attack", L"DoubleJump" };

GamePos DunPlayer::GetColorPos( )
{
	return mPos * 0.02f;
}

void DunPlayer::EnterCollision(DunCollider* _left, DunCollider* _right)
{
	_left->SetHp(_left->GetHp( ) - mDamage);
	_right;
	//if ( 0 >= _left->GetHp( ) )
	//{
	//	DunActor* actor = (DunActor*)(&_left->GetActor( ));
	//	actor->Die( );
	//}
}

DunPlayer::DunPlayer( )
	: meState(__PlayerState::MAX), meDir(__PlayerDirection::Right)
	, mPlayerAni(nullptr), mDustAni(nullptr), mCurRoomColImg(nullptr), mCurRoom(nullptr), mPlayerCollider(nullptr)
	, /*mPlayerLeftHand(nullptr),*/ mPlayerRightHand(nullptr), mWeapon(nullptr)
	, mDashCounter(__tag::DashCount), mMouseDir( )
	, mbCanMoveOtherRoom(true), mCurJumpHeight(0.0f), mbCanDash(true), mAttackSpeed(0.1f)
	, mFxSound(nullptr)
	//, mbCanJump(true), mbCanDoubleJump(true)
{
	mJumpPower = 500.f;

	mCheckPos[_ActorCheckDir::Left] = { 16.0f, -16.0f };
	mCheckPos[_ActorCheckDir::Right] = { -16.0f, -16.0f };
	mCheckPos[_ActorCheckDir::Top] = { 0.0f, -5.0f };
	mCheckPos[_ActorCheckDir::Bottom] = { 0.0f, 0.0f };
	mCheckPos[_ActorCheckDir::Ground] = { 0.0f, 0.0f };

	mCheckSubPos[_ActorCheckDir::Left] = { 0.0f, 0.0f };
	mCheckSubPos[_ActorCheckDir::Right] = { 0.0f, 0.0f };
	mCheckSubPos[_ActorCheckDir::Top] = { 0.0f, 0.0f };
	mCheckSubPos[_ActorCheckDir::Bottom] = { 0.0f, 0.0f };

	mPlayerCollider = CreateCollider<DunRectCollider>(L"Player_col", { 32.0f, 35.0f });
	mPlayerCollider->SetSubPivotMode(PivotDirection::Bottom);


	mFxSound = GameSound::PlaySoundOrNull( );
	if ( nullptr == mFxSound )
	{
		CRASH_PROG;
	}
}

DunPlayer::~DunPlayer( )
{
	EMPTY_STATEMENT;
}

bool DunPlayer::Init( )
{
	SetHp(_PlayerAbility::HP);
	SetDamage(_PlayerAbility::Damage);
	SetSpeed(_PlayerAbility::Speed);
	SetJumpPower(_PlayerAbility::JumpPower);

	InitAllAnimation( );

	ChangeState(__PlayerState::Idle);

	return true;
}

void DunPlayer::Update( )
{
	if ( true == GameKeyInput::Down(L"F8") )
	{
		mPos = Geometry::CorrectionValue;
	}

	UpdateCursorDir( );
	ApplyGravity( );
	CheckMovement( );
	CheckTopWall( );
	UpdateHandPos( );
	UpdateCharDir( );
	UpdateWeaponDir( );

	switch ( meState )
	{
	case DunPlayer::__PlayerState::Die:
		Die( );
		break;
	case DunPlayer::__PlayerState::Idle:
		Idle( );
		break;
	case DunPlayer::__PlayerState::Jump:
		Jump( );
		break;
	case DunPlayer::__PlayerState::Run:
		Run( );
		break;
	case DunPlayer::__PlayerState::Walk:
		Walk( );
		break;
	case DunPlayer::__PlayerState::Attack:
		Attack( );
		break;
	case DunPlayer::__PlayerState::DoubleJump:
		DoubleJump( );
		break;
	case DunPlayer::__PlayerState::MAX: FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	//DunSceneManager& sceneMgr = DunSceneManager::Instance( );
	DunSceneManager::Instance( ).GetCurSceneOrNull( ) \
		->SetCameraPos(mPos - Geometry::CorrectionValue);
}

void DunPlayer::Collide( )
{
}

void DunPlayer::ApplyGravity( )
{
	if ( false == IsWall(_ActorCheckDir::Bottom)
		&& false == IsWall(_ActorCheckDir::Bottom, Geometry::ZeroPos, GameColor::Red) )
	{
		SetPos(mPos + (Gravity * GameTime::DeltaTime( )));
	}
	else
	{
		while ( true == IsWall(_ActorCheckDir::Bottom, GamePos(0.f, -1.f) + Geometry::BottomDirPos, GameColor::Red) )
		{
			SetYPos(mPos.mY - (1.0f));
		}

		while ( true == IsWall(_ActorCheckDir::Bottom, Geometry::BottomDirPos) )
		{
			SetYPos(mPos.mY - (1.0f));
		}

		mCurJumpHeight = 0.0f;
		mDashCounter = __tag::DashCount;
		mDashPos = Geometry::ZeroPos;
	}
}

void DunPlayer::CheckMovement( )
{
	if ( true == GameKeyInput::Press(L"Left") )
	{
		while ( true == IsWall(_ActorCheckDir::Right, Geometry::RightDirPos) )
		{
			SetXPos(mPos.mX + 1.0f);
		}
	}
	else if ( true == GameKeyInput::Press(L"Right") )
	{
		while ( true == IsWall(_ActorCheckDir::Left, Geometry::LeftDirPos) )
		{
			SetXPos(mPos.mX - 1.0f);
		}
	}
}

void DunPlayer::CheckTopWall( )
{
	while ( true == IsWall(_ActorCheckDir::Top, Geometry::TopDirPos) )
	{
		SetYPos(mPos.mY + (1.0f));
	}
}

void DunPlayer::UpdateHandPos( )
{
	mPlayerRightHand->SetSubRectPos((GetColorPos( ) * mMouseDir) + GamePos(4.f, -16.f));
}

void DunPlayer::UpdateCharDir( )
{
	__PlayerDirection prevDir = meDir;

	// -90 ~ 90
	if ( -90.f <= mMouseDir.DirToAngle( ) && 90.f >= mMouseDir.DirToAngle( ) )
	{
		meDir = __PlayerDirection::Right;
	}
	else
	{
		meDir = __PlayerDirection::Left;
	}

	if ( prevDir != meDir )
	{
		ChangeState(meState);
	}
}

void DunPlayer::UpdateCursorDir( )
{
	mMouseDir = DungreedCore::MainWindow( ).GetMousePos( ) - Geometry::CorrectionValue;
	mMouseDir.Normalize( );
}

void DunPlayer::UpdateWeaponDir( )
{
	std::wstring str = L"weapon_";
	float angle = mMouseDir.DirToAngle( ) + 90;
	int weapon_ani = (int)(angle / 15) + 1;
	str.append(std::to_wstring(weapon_ani)).append(L".bmp");

	mWeapon->SetSubRectPos((GetColorPos( ) * mMouseDir) + GamePos(-85.f, -120.f));
	mWeapon->SetSprite(str);
}

bool DunPlayer::IsWall(_ActorCheckDir _dir, GamePos _pos, GameColor _color)
{
	if ( nullptr == mCurRoomColImg ) // 게임 시작시에는 세팅이 안되어 있으므로
	{
		return false;
	}

	const GameColor& pixelColor = \
		mCurRoomColImg->GetSprite( ).PosToColor((GetCheckedPos(_dir) + _pos));

	if ( _color == pixelColor.GetColor( ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DunPlayer::SetCurRoom(RoomData* _room)
{
	mCurRoom = _room;

	for ( auto& iter : mCurRoom->mAllMonster )
	{
		//iter->mCurRoomColImg = mCurRoomColImg;
		iter->SetPos(
			GamePos(
				Well512Random::Instance( ).GetFloatValue(300.f, 400.f),
				Well512Random::Instance( ).GetFloatValue(200.f, 400.f)
			)
		);
	}

}

RoomData* DunPlayer::GetCurRoom( )
{
	return mCurRoom;
}
