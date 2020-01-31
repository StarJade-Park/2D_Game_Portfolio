#pragma once
#include <vector>

#include <..\psklib\GameColor.h>

#include "DunActor.h"
#include "DunObjectAbility.h"

class DunAniRender;
class DunTransRender;
class DunRoom;
class RoomData;
class DunRectCollider;
class GameSoundPlayer;

class DunPlayer
	: public DunActor, public DunObjectAbility
{
	friend DunActor;
#pragma region enums
public:
	// - Die, Idle, Jump, Run, Walk, Attack, DoubleJump, MAX
	enum class __PlayerState
	{
		Die, Idle, Jump, Run, Walk, Attack, DoubleJump, MAX
	};

	enum class __PlayerDirection
	{
		Left, Right, MAX
	};

	enum _AniIndex
	{
		Start		= 0,
		IdleEnd		= 5,
		DieEnd		= 1,
		JumpEnd		= 1,
		RunEnd		= 7,
		WalkEnd		= 6,
		DustEnd		= 6,
	};

	enum _PlayerAbility
	{
		HP = 1000,
		Damage = 50,
		Speed = 400,
		JumpPower = 1000,
	};

	enum __tag
	{
		DashCount = 4,
		ObjectOrder = 0,
		PlayerFx = 1,
		PlayerHand = 2,
	};
#pragma endregion

public:
#pragma region sigleton
	static DunPlayer& Instance( )
	{
		static DunPlayer* player = nullptr;
		if ( nullptr == player )
		{
			player = DunActor::CreateActor<DunPlayer>(L"Player", true);
		}

		return *player;
	}
#pragma endregion

#pragma region state
	void Die( );
	void Idle( );
	void Jump( );
	void Run( );
	void Walk( );
	void Attack( );
	void DoubleJump( );

	void ChangeState(DunPlayer::__PlayerState _state);
#pragma endregion

	void InitAllAnimation( );

	void SetCurRoom(RoomData* _room);
	RoomData* GetCurRoom( );

	void ApplyGravity( );
	void CheckMovement( );
	void CheckTopWall( );

	void UpdateHandPos( );
	void UpdateCharDir( );
	void UpdateCursorDir( );
	void UpdateWeaponDir( );

	bool IsWall(_ActorCheckDir _dir, GamePos _pos = Geometry::ZeroPos, GameColor _color = GameColor::Lime);

	void OnAbleMoveToOtherRoom( )
	{
		mbCanMoveOtherRoom = true;
	}

	void OffAbleMoveToOtherRoom( )
	{
		mbCanMoveOtherRoom = false;
	}

	bool IsCanMoveOtherRoom( ) const
	{
		return mbCanMoveOtherRoom;
	}

	void SetColImg(DunTransRender* _roomColImg)
	{
		mCurRoomColImg = _roomColImg;
	}

	GamePos GetColorPos( );

	void EnterCollision(DunCollider* _left, DunCollider* _right) override;

private:
	DunPlayer( );
	~DunPlayer( );

	bool Init( ) override;
	void Update( ) override;
	void Collide( ) override;

private:
	static std::wstring mAniNames[static_cast<size_t>(__PlayerState::MAX)];

	__PlayerState meState;
	__PlayerDirection meDir;

	DunRectCollider* mPlayerCollider;

#pragma region animation
	DunAniRender* mPlayerAni;
	DunAniRender* mDustAni;
#pragma endregion
	DunTransRender* mPlayerRightHand;
	DunTransRender* mWeapon;

	RoomData* mCurRoom;
	DunTransRender* mCurRoomColImg;

	GamePos mDashPos;

	bool mbCanMoveOtherRoom;
	bool mbCanDash;

	float mCurJumpHeight;
	float mAttackSpeed;

	GameSoundPlayer* mFxSound;

public:
	GamePos mMouseDir;
	unsigned int mDashCounter;
};

