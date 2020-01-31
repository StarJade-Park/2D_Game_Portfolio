#pragma once
#include "DunActor.h"
#include "DunObjectAbility.h"

class DunTransRender;
class DunAniRender;

class SwordFx
	: public DunActor, public DunObjectAbility
{
public:
	SwordFx( );
	~SwordFx( );

	bool Init( ) override;
	void Update( ) override;

	DunTransRender& GetRender( )
	{
		return *mRender;
	}

	void SetColName(std::wstring _colName)
	{
		mColName = _colName;
	}

	//void SetDamage(int _damage)
	//{
	//	mDamage = _damage;
	//}

private:
	float mDeathTime;
	DunTransRender* mRender;
	GameSize mColSize;
	//int mDamage;
	std::wstring mColName;
	//GamePos Power;
};

