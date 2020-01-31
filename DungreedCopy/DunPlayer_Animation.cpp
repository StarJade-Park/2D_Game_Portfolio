#include "DunPlayer.h"
#include "DunAniRender.h"
#include "DunTransRender.h"

void DunPlayer::InitAllAnimation( )
{
#pragma region animation_player
	// Die, Idle, Jump, Run, Walk, Attack, DoubleJump, MAX
	mPlayerAni = DunActor::CreateRender<DunAniRender>(__tag::ObjectOrder);
	mPlayerAni->SetSubPivotMode(PivotDirection::Bottom);

	// left
	mPlayerAni->CreateAnimation(L"L_Die", L"L_Die.bmp", _AniIndex::Start, _AniIndex::DieEnd - 1, false);
	mPlayerAni->CreateAnimation(L"L_Idle", L"L_Idle.bmp", _AniIndex::Start, _AniIndex::IdleEnd - 1, true);
	mPlayerAni->CreateAnimation(L"L_Jump", L"L_Jump.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);
	mPlayerAni->CreateAnimation(L"L_Run", L"L_Run.bmp", _AniIndex::Start, _AniIndex::RunEnd - 1, true);
	mPlayerAni->CreateAnimation(L"L_Walk", L"L_Walk.bmp", _AniIndex::Start, _AniIndex::WalkEnd - 1, true);

	mPlayerAni->CreateAnimation(L"L_Attack", L"L_Attack.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);
	mPlayerAni->CreateAnimation(L"R_Attack", L"R_Attack.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);

	// right
	mPlayerAni->CreateAnimation(L"R_Die", L"R_Die.bmp", _AniIndex::Start, _AniIndex::DieEnd - 1, false);
	mPlayerAni->CreateAnimation(L"R_Idle", L"R_Idle.bmp", _AniIndex::Start, _AniIndex::IdleEnd - 1, true);
	mPlayerAni->CreateAnimation(L"R_Jump", L"R_Jump.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);
	mPlayerAni->CreateAnimation(L"R_Run", L"R_Run.bmp", _AniIndex::Start, _AniIndex::RunEnd - 1, true);
	mPlayerAni->CreateAnimation(L"R_Walk", L"R_Walk.bmp", _AniIndex::Start, _AniIndex::WalkEnd - 1, true);

	mPlayerAni->CreateAnimation(L"L_DoubleJump", L"L_DoubleJump.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);
	mPlayerAni->CreateAnimation(L"R_DoubleJump", L"R_DoubleJump.bmp", _AniIndex::Start, _AniIndex::JumpEnd - 1, false);


#pragma endregion

#pragma region run_dust
	mDustAni = DunActor::CreateRender<DunAniRender>(__tag::PlayerFx);
	mDustAni->SetSubPivotMode(PivotDirection::Bottom);

	mDustAni->CreateAnimation(L"Idle_Run_Dust", L"Idle_Run_Dust.bmp", 0, 0, true);
	mDustAni->CreateAnimation(L"L_Run_Dust", L"L_Run_Dust.bmp", _AniIndex::Start, _AniIndex::DustEnd - 1, true);
	mDustAni->CreateAnimation(L"R_Run_Dust", L"R_Run_Dust.bmp", _AniIndex::Start, _AniIndex::DustEnd - 1, true);
#pragma endregion

	mPlayerRightHand = CreateRender<DunTransRender>(__tag::PlayerHand);
	mPlayerRightHand->SetSprite(L"Char_Hand.bmp");

	mWeapon = CreateRender<DunTransRender>(__tag::PlayerHand);
	mWeapon->SetSubRectSize(GameSize(200.f, 200.f));

	//mWeaponFx = CreateRender<DunTransRender>(__tag::PlayerHand);
	//mWeaponFx->SetSubRectSize(GameSize(300.f, 300.f));
}
