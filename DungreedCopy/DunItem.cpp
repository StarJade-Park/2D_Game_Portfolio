#include "DunItem.h"
#include "DunAniRender.h"


DunItem::DunItem( )
	: mWeaponImg(nullptr)
	, mDamage(0)
{
	mWeaponImg = DunActor::CreateRender<DunAniRender>(1);
	// todo 24�� �ִϸ��̼� ����
	//mWeaponImg->CreateAnimation( );
}


DunItem::~DunItem( )
{
}
