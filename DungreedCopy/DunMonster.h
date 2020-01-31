#pragma once
#include <..\psklib\GameColor.h>

#include "DunActor.h"
#include "DunObjectAbility.h"

class DunAniRender;
class DunRectCollider;
class GameSoundPlayer;
class DunTransRender;
class RoomData;

class DunMonster
	: public DunActor, public DunObjectAbility
{
public:
	enum _MonDir
	{
		Left, Right, InValid
	};

	enum class __MonsterState
	{
		Die, Idle, Walk, Attack, MAX
	};

public:
	DunMonster( );
	~DunMonster( );

	bool Init( ) override;
	void Update( ) override;
	void ChangeState(__MonsterState _state);

	void ApplyGravity( );
	void CheckMovement( );
	void UpdateMonDir( );

	void Die( );
	void Idle( );
	void Walk( );
	void Attack( );

	bool IsWall(_ActorCheckDir _dir, GamePos _pos = Geometry::ZeroPos, GameColor _color = GameColor::Lime);

	void EnterCollision(DunCollider* _left, DunCollider* _right) override;

public:
	static GameSize AttackSize;
	static GameSize IdleSize;

	DunAniRender* mMonsterAni;
	DunRectCollider* mMonsterCollider;
	GameSoundPlayer* mFxSound;
	float mAttackSpeed;
	float mIdleTime;
	DunTransRender* mCurRoomColImg;
	__MonsterState meState;
	_MonDir meDir;

	RoomData* mSpawnRoom;
};

