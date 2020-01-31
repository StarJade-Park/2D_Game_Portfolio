#include <Windows.h>

#include "GameCircle.h"
#include "Debug.h"

float GameCircle::GetLeft( ) const
{
	float result = 0.0f;

	switch ( mePivot )
	{
	case PivotDirection::LeftTop:
		result = mPos.mX;
		break;
	case PivotDirection::Top:
		CRASH_PROG;
		break;
	case PivotDirection::RightTop:
		CRASH_PROG;
		break;
	case PivotDirection::Right:
		CRASH_PROG;
		break;
	case PivotDirection::RightBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Bottom:
		CRASH_PROG;
		break;
	case PivotDirection::LeftBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Left:
		CRASH_PROG;
		break;
	case PivotDirection::Centor:
		result = mPos.mX - mRadius;
		break;
	case PivotDirection::Custom:
		CRASH_PROG;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameCircle::GetRight( ) const
{
	float result = 0.0f;

	switch ( mePivot )
	{
	case PivotDirection::LeftTop:
		result = mPos.mX + (mRadius * 2.0f);
		break;
	case PivotDirection::Top:
		CRASH_PROG;
		break;
	case PivotDirection::RightTop:
		CRASH_PROG;
		break;
	case PivotDirection::Right:
		CRASH_PROG;
		break;
	case PivotDirection::RightBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Bottom:
		CRASH_PROG;
		break;
	case PivotDirection::LeftBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Left:
		CRASH_PROG;
		break;
	case PivotDirection::Centor:
		result = mPos.mX - mRadius;
		break;
	case PivotDirection::Custom:
		CRASH_PROG;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameCircle::GetTop( ) const
{
	float result = 0.0f;

	switch ( mePivot )
	{
	case PivotDirection::LeftTop:
		result = mPos.mY;
		break;
	case PivotDirection::Top:
		CRASH_PROG;
		break;
	case PivotDirection::RightTop:
		CRASH_PROG;
		break;
	case PivotDirection::Right:
		CRASH_PROG;
		break;
	case PivotDirection::RightBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Bottom:
		CRASH_PROG;
		break;
	case PivotDirection::LeftBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Left:
		CRASH_PROG;
		break;
	case PivotDirection::Centor:
		result = mPos.mY - mRadius;
		break;
	case PivotDirection::Custom:
		CRASH_PROG;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameCircle::GetBottom( ) const
{
	float result = 0.0f;

	switch ( mePivot )
	{
	case PivotDirection::LeftTop:
		result = mPos.mY + (mRadius * 2.0f);
		break;
	case PivotDirection::Top:
		CRASH_PROG;
		break;
	case PivotDirection::RightTop:
		CRASH_PROG;
		break;
	case PivotDirection::Right:
		CRASH_PROG;
		break;
	case PivotDirection::RightBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Bottom:
		CRASH_PROG;
		break;
	case PivotDirection::LeftBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Left:
		CRASH_PROG;
		break;
	case PivotDirection::Centor:
		result = mPos.mY + mRadius;
		break;
	case PivotDirection::Custom:
		CRASH_PROG;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}
