#include <string>

#include <..\psklib\GameTime.h>
#include <..\psklib\GameKeyInput.h>
#include <..\psklib\Debug.h>
#include <..\psklib\GameSoundSystem.h>

#include "DunPlayer.h"
#include "DungreedCore.h"
#include "DunAniRender.h"
#include "DunTransRender.h"
#include "DunSceneManager.h"
#include "RoomData.h"
#include "SwordFx.h"

void DunPlayer::Idle( )
{
	if ( true == GameKeyInput::Press(L"Left"))
	{
		ChangeState(__PlayerState::Walk);
	}
	else if ( true == GameKeyInput::Press(L"Right") )
	{
		ChangeState(__PlayerState::Walk);
	}

	if ( true == GameKeyInput::Down(L"Up"))
	{
		mFxSound->Play(L"jump.wav", 0);
		ChangeState(__PlayerState::Jump);
	}

	if ( true == GameKeyInput::Down(L"RMB") )
	{
		mFxSound->Play(L"dash.wav", 0);
		ChangeState(__PlayerState::Run);
	}

	if ( true == GameKeyInput::Down(L"LMB") )
	{
		ChangeState(__PlayerState::Attack);
	}

	if ( true == GameKeyInput::Press(L"Down") && true == GameKeyInput::Press(L"Space") )
	{
		ChangeState(__PlayerState::DoubleJump);
	}
}

void DunPlayer::Walk( )
{
	if ( true == GameKeyInput::Press(L"Left") )
	{
		SetXPos(GetPos( ).mX - GetSpeed( ) * GameTime::DeltaTime( ));
	}
	else if ( true == GameKeyInput::Press(L"Right") )
	{
		SetXPos(GetPos( ).mX + GetSpeed( ) * GameTime::DeltaTime( ));
	}

	if ( true == GameKeyInput::Up(L"Left") || true == GameKeyInput::Up(L"Right") )
	{
		ChangeState(__PlayerState::Idle);
	}

	if ( true == GameKeyInput::Down(L"Up") )
	{
		mFxSound->Play(L"jump.wav", 0);
		ChangeState(__PlayerState::Jump);
	}

	if ( true == GameKeyInput::Down(L"RMB") )
	{
		mFxSound->Play(L"dash.wav", 0);
		ChangeState(__PlayerState::Run);
	}

	if ( true == GameKeyInput::Down(L"LMB") )
	{
		ChangeState(__PlayerState::Attack);
	}

}

void DunPlayer::Run( )
{
	if ( 0 == mDashCounter )
	{
		ChangeState(__PlayerState::Idle);
		return;
	}

	if ( true == GameKeyInput::Down(L"RMB"))
	{
		--mDashCounter;
		mDashPos = Geometry::ZeroPos;
		UpdateCursorDir( );
		ChangeState(__PlayerState::Run);
	}

	if ( DunObjectAbility::DashLimit.Magnitude( ) > mDashPos.Magnitude( ) )
	{
		// note dash power 변수화
		mDashPos += (GamePos(2000.f, 2000.f) * mMouseDir) * GameTime::DeltaTime( );
		mPos = mPos + (GamePos(2000.f, 2000.f) * mMouseDir) * GameTime::DeltaTime( );
		return;
	}

	//mPos = mPos + (GamePos(5000.f, 5000.f) * mMouseDir) * GameTime::DeltaTime( );

	//--mDashCounter;

	ChangeState(__PlayerState::Idle);
}

void DunPlayer::Jump( )
{
	// 한 번 누르면 최소 높이까지
	if ( DunObjectAbility::MinJumpHeight >= mCurJumpHeight )
	{
		mCurJumpHeight += (GetJumpPower( ) * GameTime::DeltaTime( ));
		SetYPos(mPos.mY - (GetJumpPower( ) * GameTime::DeltaTime( )));

		if ( true == GameKeyInput::Press(L"Left") )
		{
			SetXPos(GetPos( ).mX - GetSpeed( ) * GameTime::DeltaTime( ));
		}
		else if ( true == GameKeyInput::Press(L"Right") )
		{
			SetXPos(GetPos( ).mX + GetSpeed( ) * GameTime::DeltaTime( ));
		}

		return;
	}
	else if ( true == GameKeyInput::Press(L"Up") )
	{
		if ( true == GameKeyInput::Press(L"Left") )
		{
			SetXPos(GetPos( ).mX - GetSpeed( ) * GameTime::DeltaTime( ));
		}
		else if ( true == GameKeyInput::Press(L"Right") )
		{
			SetXPos(GetPos( ).mX + GetSpeed( ) * GameTime::DeltaTime( ));
		}

		// 최대 높이까지
		if ( DunObjectAbility::JumpLimit <= mCurJumpHeight )
		{
			ChangeState(__PlayerState::Idle);
			return;
		}

		mCurJumpHeight += (GetJumpPower( ) * GameTime::DeltaTime( ));
		SetYPos(GetPos( ).mY - (GetJumpPower( ) * GameTime::DeltaTime( )));

		return;
	}

	ChangeState(__PlayerState::Idle);
}

// down jump
void DunPlayer::DoubleJump( )
{
	if ( true == IsWall(_ActorCheckDir::Bottom, Geometry::ZeroPos, GameColor::Red))
	{
		SetYPos(GetPos( ).mY + (5000.f * GameTime::DeltaTime( )));
	}
	ChangeState(__PlayerState::Idle);
}

void DunPlayer::Attack( )
{
	
	mAttackSpeed -= GameTime::DeltaTime( );

	if ( 0 <= mAttackSpeed )
	{
		return;
	}
	else
	{
		mFxSound->Play(L"swing_1.wav", 0);
		mAttackSpeed = 0.1f;
	}

	SwordFx* swordFx = DunActor::CreateActor<SwordFx>( );
	swordFx->SetColName(L"player_sword");
	swordFx->SetDamage(GetDamage( ));

	std::wstring str = mWeapon->GetSprite( ).GetImage( ).GetName( );
	size_t cutSize = str.find_last_of(L'_', str.size( ));
	str = str.replace(0, cutSize + 1, L"");
	std::wstring fx = L"weapon_fx_";
	fx.append(str);
	swordFx->GetRender( ).SetSprite(fx);
	swordFx->SetPos(mPos + GamePos(0.f, -50.f));

	ChangeState(__PlayerState::Idle);
}

void DunPlayer::Die( )
{
	// chage scene -> town
	//DunSceneManager::Instance( ).ChanageSceneByName(L"Town");
	ChangeState(__PlayerState::Idle);
}

void DunPlayer::ChangeState(DunPlayer::__PlayerState _state)
{
	std::wstring newAniName = L"";

	switch ( meDir )
	{
	case DunPlayer::__PlayerDirection::Left:
		newAniName.append(L"L_");
		break;
	case DunPlayer::__PlayerDirection::Right:
		newAniName.append(L"R_");
		break;
	default:
		CRASH_PROG;
		break;
	}

	if ( __PlayerState::Walk == _state )
	{
		std::wstring dustAni = newAniName + L"Run_Dust";
		mDustAni->PlayAnimation(dustAni.c_str( ));
	}
	else
	{
		mDustAni->PlayAnimation(L"Idle_Run_Dust");
	}

	//assert(!(DunPlayer::__PlayerState::MAX > _state));
	newAniName.append(mAniNames[static_cast<int>(_state)]);

	// TODO: 애니메이션 리소스 제작
	mPlayerAni->PlayAnimation(newAniName.c_str( ));
	meState = _state;
}
