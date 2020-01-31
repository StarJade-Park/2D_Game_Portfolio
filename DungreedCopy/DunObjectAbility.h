#pragma once
#include <..\psklib\tags.h>

class GamePos;

class DunObjectAbility
{
public:
	virtual void SetHp(int _hp)
	{
		mHp = _hp;
	}

	virtual int GetHp( ) const
	{
		return mHp;
	}

	virtual void SetDamage(int _damage)
	{
		mDamage = _damage;
	}

	virtual int GetDamage( ) const
	{
		return mDamage;
	}

	virtual void SetSpeed(float _speed)
	{
		mSpeed = _speed;
	}

	virtual float GetSpeed( ) const
	{
		return mSpeed;
	}

	virtual void SetJumpPower(float _jumpPower)
	{
		mJumpPower = _jumpPower;
	}

	virtual float GetJumpPower( ) const
	{
		return mJumpPower;
	}

protected:
	DunObjectAbility( )
		: mHp(def::__tag::InvalidValue)
		, mDamage(def::__tag::InvalidValue)
		, mSpeed(def::__tag::InvalidValue)
		, mJumpPower(def::__tag::InvalidValue)
	{
		EMPTY_STATEMENT;
	}

	~DunObjectAbility( ) = default;

protected:
	int mHp;
	int mDamage;
	float mSpeed;
	float mJumpPower;
	static GamePos Gravity;
	static GamePos DashLimit;
	static float JumpLimit;
	static float MinJumpHeight;
};

