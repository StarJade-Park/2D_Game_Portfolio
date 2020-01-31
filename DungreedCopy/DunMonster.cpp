#include <..\psklib\GameSoundSystem.h>
#include <..\psklib\GameTime.h>

#include "DunMonster.h"
#include "DunAniRender.h"
#include "DunRectCollider.h"
#include "DunTransRender.h"
#include "DunPlayer.h"
#include "SwordFx.h"
#include "RoomData.h"

GameSize DunMonster::AttackSize = GameSize(320.f, 192.f);
GameSize DunMonster::IdleSize = GameSize(200.f, 128.f);

DunMonster::DunMonster( )
	: mMonsterAni(nullptr), mMonsterCollider(nullptr), mFxSound(nullptr), mCurRoomColImg(nullptr)
	, mAttackSpeed(1.0f), meState(__MonsterState::Idle), mIdleTime(10.f)
{
	SetHp(100);
	SetDamage(5);
	SetSpeed(200.f);
	mPos = GamePos(-999.f, -999.f);

	mMonsterAni = CreateRender<DunAniRender>(0);
	mMonsterAni->CreateAnimation(L"L_SkelIdle", L"L_SkelIdle.bmp", 0, 5, true);
	mMonsterAni->CreateAnimation(L"R_SkelIdle", L"R_SkelIdle.bmp", 0, 5, true);
	mMonsterAni->CreateAnimation(L"L_SkelAttack", L"L_SkelAttack.bmp", 0, 11, true, 0.11f);
	mMonsterAni->CreateAnimation(L"R_SkelAttack", L"R_SkelAttack.bmp", 0, 11, true, 0.11f);
	mMonsterAni->CreateAnimation(L"L_SkelMove", L"L_SkelMove.bmp", 0, 5, true);
	mMonsterAni->CreateAnimation(L"R_SkelMove", L"R_SkelMove.bmp", 0, 5, true);
	mMonsterAni->SetSubRectSize(IdleSize);

	mMonsterCollider = CreateCollider<DunRectCollider>(L"Monster", GameSize(100.f, 128.f));
	mMonsterCollider->SetSubPivotMode(PivotDirection::Bottom);

	mFxSound = GameSound::PlaySoundOrNull( );
	if ( nullptr == mFxSound )
	{
		CRASH_PROG;
	}
}

DunMonster::~DunMonster( )
{
}

bool DunMonster::Init( )
{
	return true;
}

void DunMonster::Update( )
{
	ApplyGravity( );
	CheckMovement( );
	UpdateMonDir( );

	if ( 0 >= mHp )
	{
		meState = __MonsterState::Die;
	}

	switch ( meState )
	{
	case DunMonster::__MonsterState::Die:
		Die( );
		break;
	case DunMonster::__MonsterState::Idle:
		Idle( );
		break;
	case DunMonster::__MonsterState::Walk:
		Walk( );
		break;
	case DunMonster::__MonsterState::Attack:
		Attack( );
		break;
	case DunMonster::__MonsterState::MAX: FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}
}

void DunMonster::ChangeState(__MonsterState _state)
{
	switch ( _state )
	{
	case DunMonster::__MonsterState::Die:
		meState = __MonsterState::Die;
		break;
	case DunMonster::__MonsterState::Idle:
		meState = __MonsterState::Idle;
		break;
	case DunMonster::__MonsterState::Walk:
		meState = __MonsterState::Walk;
		break;
	case DunMonster::__MonsterState::Attack:
		meState = __MonsterState::Attack;
		break;
	case DunMonster::__MonsterState::MAX: FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}
}

bool DunMonster::IsWall(_ActorCheckDir _dir, GamePos _pos, GameColor _color)
{
	if ( nullptr == mCurRoomColImg ) // 게임 시작시에는 세팅이 안되어 있으므로
	{
		return false;
	}

	const GameColor& pixelColor = \
		mCurRoomColImg->GetSprite( ).PosToColor((GetCheckedPos(_dir) + _pos));

	GamePos test = GetCheckedPos(_dir) + _pos;

	if ( _color == pixelColor.GetColor( ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DunMonster::EnterCollision(DunCollider* _left, DunCollider* _right)
{
	_left->SetHp(_left->GetHp( ) - _right->GetDamage( ));

	if ( 0 >= _left->GetHp( ) )
	{
		mFxSound->Play(L"Die.wav", 0);
		DunActor* actor = (DunActor*)(&_left->GetActor( ));

		mSpawnRoom->mAllMonster.erase(
			std::find(mSpawnRoom->mAllMonster.begin( ), mSpawnRoom->mAllMonster.end( ), actor)
		);

		actor->Die( );
	}
}

void DunMonster::ApplyGravity( )
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
	}
}

void DunMonster::CheckMovement( )
{
	//switch ( meDir )
	//{
	//case DunMonster::Left:
	//	if ( __MonsterState::Walk == meState )
	//	{
	//		while ( true == IsWall(_ActorCheckDir::Right, Geometry::RightDirPos) )
	//		{
	//			SetXPos(mPos.mX + 1.0f);
	//		}
	//	}
	//	break;
	//case DunMonster::Right:
	//	if ( __MonsterState::Walk == meState )
	//	{
	//		while ( true == IsWall(_ActorCheckDir::Left, Geometry::LeftDirPos) )
	//		{
	//			SetXPos(mPos.mX - 1.0f);
	//		}
	//	}
	//	break;
	//case DunMonster::InValid:
	//	break;
	//default:
	//	break;
	//}
}

void DunMonster::UpdateMonDir( )
{
	_MonDir prevDir = meDir;

	if ( mPos.mX >= DunPlayer::Instance( ).GetPos( ).mX )
	{
		meDir = _MonDir::Left;
	}
	else
	{
		meDir = _MonDir::Right;
	}

	if ( prevDir != meDir )
	{
		ChangeState(meState);
	}
}

void DunMonster::Die( )
{
	//mMonsterAni->SetSubRectSize(IdleSize);

	//mFxSound->Play(L"MonsterDie.wav", 0);
	//mbIsDied = true;
}

void DunMonster::Idle( )
{
	mMonsterAni->SetSubRectSize(IdleSize);
	float moveVal = DunPlayer::Instance( ).GetPos( ).mX - mPos.mX;
	
	switch ( meDir )
	{
	case DunMonster::Left:
		mMonsterAni->PlayAnimation(L"L_SkelIdle");
		if ( 100.f >= abs(moveVal) )
		{
			ChangeState(__MonsterState::Walk);
		}
		break;
	case DunMonster::Right:
		mMonsterAni->PlayAnimation(L"R_SkelIdle");
		if ( 100.f >= abs(moveVal) )
		{
			ChangeState(__MonsterState::Walk);
		}
		break;
	case DunMonster::InValid: CRASH_PROG;
	default:
		break;
	}
}

void DunMonster::Walk( )
{
	mMonsterAni->SetSubRectSize(IdleSize);
	GamePos attckPos = DunPlayer::Instance( ).GetPos( ) - mPos;

	switch ( meDir )
	{
	case DunMonster::Left:
		if ( 50.f >= attckPos.Magnitude( ) )
		{
			ChangeState(__MonsterState::Attack);
			break;
		}
		mMonsterAni->PlayAnimation(L"L_SkelMove");
		mPos.mX -= mSpeed * GameTime::DeltaTime( );
		break;
	case DunMonster::Right:
		if ( 50.f >= attckPos.Magnitude( ) )
		{
			ChangeState(__MonsterState::Attack);
			break;
		}
		mMonsterAni->PlayAnimation(L"R_SkelMove");
		mPos.mX += mSpeed * GameTime::DeltaTime( );
		break;
	case DunMonster::InValid:
	default:
		break;
	}
}

void DunMonster::Attack( )
{
	mAttackSpeed -= GameTime::DeltaTime( );

	if ( 0 <= mAttackSpeed )
	{
		ChangeState(meState);
		return;
	}
	else
	{
		mAttackSpeed = 1.5f;
	}

	mMonsterAni->SetSubRectSize(AttackSize);
	GamePos attckPos = DunPlayer::Instance( ).GetPos( ) - mPos;
	SwordFx* swordFx = DunActor::CreateActor<SwordFx>( );
	swordFx->SetDamage(GetDamage( ));
	swordFx->SetColName(L"mon_sword");
	swordFx->SetPos(mPos + GamePos(0.f, -50.f));

	switch ( meDir )
	{
	case DunMonster::Left:
		if ( 50.f <= attckPos.Magnitude( ) )
		{
			ChangeState(__MonsterState::Idle);
			break;
		}
		mFxSound->Play(L"swing_2.wav", 0);
		mMonsterAni->PlayAnimation(L"L_SkelAttack");
		
		break;
	case DunMonster::Right:
		if ( 50.f <= attckPos.Magnitude( ) )
		{
			ChangeState(__MonsterState::Idle);
			break;
		}
		mFxSound->Play(L"swing_2.wav", 0);
		mMonsterAni->PlayAnimation(L"R_SkelAttack");
		break;
	case DunMonster::InValid: CRASH_PROG;
	default:
		break;
	}
}
