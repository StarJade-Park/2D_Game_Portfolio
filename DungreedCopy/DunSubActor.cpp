#include "DunSubActor.h"
#include "DunSceneManager.h"
#include "DunActor.h"

GamePos DunSubActor::GetActorPos( )
{
	if ( false == mbCameraEffect )
	{
		return mActor->GetPos( );
	}
	else // camera effect on
	{
		return mActor->GetPos( ) \
			- DunSceneManager::Instance( ).GetCurSceneOrNull( )->GetCameraPos( );
	}
}

void DunSubActor::SetActorPos(GamePos _pos)
{
	mActor->SetPos(_pos);
}

GamePos DunSubActor::CalcPivotPos( )
{
	GamePos pivotPos = \
		GamePos(mSubRect.GetSize( ).mX * -0.5f, mSubRect.GetSize( ).mY * -0.5f);

	switch ( mePivot )
	{
	case PivotDirection::LeftTop:
		pivotPos.mX -= pivotPos.mX;
		pivotPos.mY -= pivotPos.mY;
		break;
	case PivotDirection::Top:
		pivotPos.mY -= pivotPos.mY;
		break;
	case PivotDirection::RightTop:
		pivotPos.mX += pivotPos.mX;
		pivotPos.mY -= pivotPos.mY;
		break;
	case PivotDirection::Right:
		pivotPos.mX += pivotPos.mX;
		break;
	case PivotDirection::RightBottom:
		pivotPos.mX += pivotPos.mX;
		pivotPos.mY += pivotPos.mY;
		break;
	case PivotDirection::Bottom:
		pivotPos.mY += pivotPos.mY;
		break;
	case PivotDirection::LeftBottom:
		pivotPos.mX -= pivotPos.mX;
		pivotPos.mY += pivotPos.mY;
		break;
	case PivotDirection::Left:
		pivotPos.mX -= pivotPos.mX;
		break;
	case PivotDirection::Centor:
		EMPTY_STATEMENT;
		break;
	case PivotDirection::Custom: // 바로 return 되는 것에 유의
		return GetActorPos( ) + mSubRect.GetPos( );
		break;
	default:
		CRASH_PROG;
		break;
	}

	return GetActorPos( ) + pivotPos;
}

inline bool DunSubActor::IsCanUpdate( )
{
	return DunObject::IsCanUpdate( ) && mActor->IsCanUpdate( );
}

inline bool DunSubActor::IsDied( )
{
	return DunObject::IsDied( ) || mActor->IsDied( );
}

DunSubActor::DunSubActor( )
	: mActor(nullptr)
	, mbCanSizeCustom(false)
	, mbCameraEffect(true)
	, mePivot(PivotDirection::Bottom)
	, mSubRect()
{
	EMPTY_STATEMENT;
}


DunSubActor::~DunSubActor( )
{
	EMPTY_STATEMENT;
}
