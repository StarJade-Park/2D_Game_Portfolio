#include <..\psklib\GameTime.h>
#include <..\psklib\GameSoundSystem.h>

#include "SwordFx.h"
#include "DunTransRender.h"
#include "DunRectCollider.h"
#include "DunPlayer.h"

SwordFx::SwordFx( )
	: mDeathTime(0.1f)
	, mRender(nullptr)
	, mColName(L"sword_fx")
{
}

SwordFx::~SwordFx( )
{
}

bool SwordFx::Init( )
{
	mRender = CreateRender<DunTransRender>(DunPlayer::__tag::PlayerFx);
	mRender->SetSubPivotMode(PivotDirection::Centor);
	mRender->SetSprite(L"Idle_Run_Dust.bmp");
	mRender->SetSubRectSize({ 300.f, 300.f });

	//collider->SetActorPos
	return true;
}

void SwordFx::Update( )
{
	mDeathTime -= GameTime::DeltaTime( );

	mColSize = GameSize(200.f, 200.f);

	/*DunRectCollider* collider = */CreateCollider<DunRectCollider>(mColName.c_str( ), mColSize);

	if ( 0 >= mDeathTime )
	{
		mbIsDied = true;
		return;
	}

}
