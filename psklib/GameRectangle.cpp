#include <Windows.h>

#include "Debug.h"
#include "GameRectangle.h"

float GameRectangle::Direction (PivotDirection _setPivot)
{
	float result = -9999.9f;
	mePivot = _setPivot;

	switch (mePivot)
	{
	case PivotDirection::LeftTop:
		result = mPos.mX + mSize.mX;
		break;
	case PivotDirection::Top:
		result = -mPos.mY;
		break;
	case PivotDirection::RightTop:
		result = mPos.mX - mSize.mX;
		break;
	case PivotDirection::Right:
		result = -mPos.mX;
		break;
	case PivotDirection::RightBottom:
		result = -mPos.mX - mSize.mX;
		break;
	case PivotDirection::Bottom:
		result = mPos.mY;
		break;
	case PivotDirection::LeftBottom:
		CRASH_PROG;
		break;
	case PivotDirection::Left:
		CRASH_PROG;
		break;
	case PivotDirection::Centor:
		CRASH_PROG;
		break;
	case PivotDirection::Custom:
		CRASH_PROG;;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameRectangle::GetLeft( ) const
{
	float result = -9999.9f;

	switch ( mePivot )
	{
	case PivotDirection::Left:			FALL_THROUGH;
	case PivotDirection::LeftTop:		FALL_THROUGH;
	case PivotDirection::LeftBottom:	FALL_THROUGH;
		result = mPos.mX;
		break;

	case PivotDirection::Right:			FALL_THROUGH;
	case PivotDirection::RightTop:		FALL_THROUGH;
	case PivotDirection::RightBottom:	FALL_THROUGH;
		result = mPos.mX - mSize.mX;
		break;
	case PivotDirection::Top:			FALL_THROUGH;
	case PivotDirection::Bottom:		FALL_THROUGH;
	case PivotDirection::Centor:		FALL_THROUGH;
		result = mPos.mX - (mSize.mX * 0.5f);
		break;
	case PivotDirection::Custom:		FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameRectangle::GetRight( ) const
{
	float result = -9999.9f;

	switch ( mePivot )
	{
	case PivotDirection::Left:			FALL_THROUGH;
	case PivotDirection::LeftTop:		FALL_THROUGH;
	case PivotDirection::LeftBottom:	FALL_THROUGH;
		result = mPos.mX + mSize.mX;
		break;

	case PivotDirection::Right:			FALL_THROUGH;
	case PivotDirection::RightTop:		FALL_THROUGH;
	case PivotDirection::RightBottom:	FALL_THROUGH;
		result = mPos.mX;
		break;
	case PivotDirection::Top:			FALL_THROUGH;
	case PivotDirection::Bottom:		FALL_THROUGH;
	case PivotDirection::Centor:		FALL_THROUGH;
		result = mPos.mX + (mSize.mX * 0.5f);
		break;
	case PivotDirection::Custom:		FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameRectangle::GetTop( ) const
{
	float result = -9999.9f;

	switch ( mePivot )
	{
	case PivotDirection::Top:			FALL_THROUGH;
	case PivotDirection::LeftTop:		FALL_THROUGH;
	case PivotDirection::RightTop:		FALL_THROUGH;
		result = mPos.mY ;
		break;
	case PivotDirection::Bottom:		FALL_THROUGH;
	case PivotDirection::LeftBottom:	FALL_THROUGH;
	case PivotDirection::RightBottom:	FALL_THROUGH;
		result = mPos.mY - mSize.mY;
		break;
	case PivotDirection::Left:			FALL_THROUGH;
	case PivotDirection::Right:			FALL_THROUGH;
	case PivotDirection::Centor:		FALL_THROUGH;
		result = mPos.mY - (mSize.mY * 0.5f);
		break;
	case PivotDirection::Custom:		FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

float GameRectangle::GetBottom( ) const
{
	float result = -9999.9f;

	switch ( mePivot )
	{
	case PivotDirection::Top:			FALL_THROUGH;
	case PivotDirection::LeftTop:		FALL_THROUGH;
	case PivotDirection::RightTop:		FALL_THROUGH;
		result = mPos.mY + mSize.mY;
		break;
	case PivotDirection::Bottom:		FALL_THROUGH;
	case PivotDirection::LeftBottom:	FALL_THROUGH;
	case PivotDirection::RightBottom:	FALL_THROUGH;
		result = mPos.mY;
		break;
	case PivotDirection::Left:			FALL_THROUGH;
	case PivotDirection::Right:			FALL_THROUGH;
	case PivotDirection::Centor:		FALL_THROUGH;
		result = mPos.mY + (mSize.mY * 0.5f);
		break;
	case PivotDirection::Custom:		FALL_THROUGH;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}
