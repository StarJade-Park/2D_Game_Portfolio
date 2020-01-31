#pragma once
#include "DunActor.h"

class DunAniRender;

class DunItem
	: public DunActor
{
public:

protected:
	DunItem( );
	virtual ~DunItem( );

protected:
	DunAniRender* mWeaponImg;
	int mDamage;
};

