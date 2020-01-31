#include "SealStone.h"
#include "DunAniRender.h"

// - enum _SealDir{ Right, Down };
SealStone::SealStone(const int _stoneCount, float _startPos, const _SealDir _dir, const int _stoneSize/* = 1*/)
	: mStartPos( ), mListOfStone( ), mDir(Invalid)
{
	mStartPos = _startPos;
	mListOfStone.resize(_stoneCount);

	for ( auto& iter : mListOfStone )
	{
		iter = DunActor::CreateRender<DunAniRender>(10);
		iter->CreateAnimation(L"Idle", L"Idle_Run_Dust.bmp", 0, 0, true);
		iter->CreateAnimation(L"Seal", L"SealStone.bmp", 0, 7, true);
		iter->SetSubRectSize(iter->GetSubRectSize( ) * (float)_stoneSize);
		iter->PlayAnimation(L"Idle");
	}

	float dir_size = -999.f; 
	switch ( _dir )
	{
	case Right:
		for ( auto& iter : mListOfStone )
		{
			iter->SetSubRectPos(GamePos(_startPos, 0.f) + Geometry::CorrectionValue);
		}
		break;
	case Down:
		for ( auto& iter : mListOfStone )
		{
			iter->SetSubRectPos(iter->GetSubRectPos( ) + GamePos(0.f, _startPos));
		}
		break;
	case Invalid: FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}
	int a = 0;
}

void SealStone::Sealed( )
{
	for ( auto& iter : mListOfStone )
	{
		iter->PlayAnimation(L"Seal");
	}
}

void SealStone::UnSealed( )
{
	for ( auto& iter : mListOfStone )
	{
		iter->PlayAnimation(L"Idle");
		//iter->SwitchDieFlag( );
	}
}
