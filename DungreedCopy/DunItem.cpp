#include "DunItem.h"
#include "DunAniRender.h"


DunItem::DunItem( )
	: mWeaponImg(nullptr)
	, mDamage(0)
{
	mWeaponImg = DunActor::CreateRender<DunAniRender>(1);
	// todo 24개 애니메이션 제작
	//mWeaponImg->CreateAnimation( );
}


DunItem::~DunItem( )
{
}
