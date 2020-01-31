#include "Geometry.h"
#include "tags.h"

const GamePos Geometry::ZeroPos = GamePos(0.0f, 0.0f);
const GamePos Geometry::RightDirPos = GamePos(-1.0f, 0.0f);
const GamePos Geometry::LeftDirPos = GamePos(1.0f, 0.0f);
const GamePos Geometry::TopDirPos = GamePos(0.0f, -32.0f);
const GamePos Geometry::BottomDirPos = GamePos(0.0f, -1.0f);
const GamePos Geometry::CorrectionValue = GamePos(def::width / 2.0f, def::height / 2.0f);
const GamePos Geometry::MouseVal = GamePos(16.f, 16.f);;

const GameSize Geometry::ZeroSize = GameSize(0.0f, 0.0f);

GameRectangle Geometry::mHorizonRect = GameRectangle( );
GameRectangle Geometry::mVerticalRect = GameRectangle( );

bool Geometry::IsColOfRectToPoint(const GameRectangle& _rect, const GamePos& _pos)
{
	if ( _rect.GetRight( ) < _pos.mX )
	{
		return false;
	}

	if ( _rect.GetLeft( ) > _pos.mX )
	{
		return false;
	}

	if ( _rect.GetTop( ) > _pos.mY )
	{
		return false;
	}

	if ( _rect.GetBottom( ) < _pos.mY )
	{
		return false;
	}

	return true;
}

bool Geometry::IsColOfRectToRect(const GameRectangle& _rect, const GameRectangle& _otherRect)
{
	if ( _rect.GetRight( ) < _otherRect.GetLeft( ) )
	{
		return false;
	}

	if ( _rect.GetLeft( ) > _otherRect.GetRight( ) )
	{
		return false;
	}

	if ( _rect.GetTop( ) > _otherRect.GetBottom( ) )
	{
		return false;
	}

	if ( _rect.GetBottom( ) < _otherRect.GetTop( ) )
	{
		return false;
	}

	return true;
}

bool Geometry::IsColOfRectToCircle(const GameRectangle& _rect, const GameCircle& _circle)
{
	mHorizonRect = _rect;
	mVerticalRect = _rect;

	mHorizonRect.mSize.mX += _circle.mRadius * 2.0f;
	mVerticalRect.mSize.mY += _circle.mRadius * 2.0f;

	if ( true == IsColOfRectToPoint(mHorizonRect, _circle.mPos) ||
		true == IsColOfRectToPoint(mVerticalRect, _circle.mPos) )
	{
		return true;
	}

	if (true == IsColOfCircleToPoint(_circle, _rect.GetLeftTop( ))  ||
		true == IsColOfCircleToPoint(_circle, _rect.GetLeftBot( ))  ||
		true == IsColOfCircleToPoint(_circle, _rect.GetRightTop( )) ||
		true == IsColOfCircleToPoint(_circle, _rect.GetRightBot( )) )
	{
		return true;
	}

	return false;
}

bool Geometry::IsColOfCircleToCircle(const GameCircle& _circle, const GameCircle& _otherCircle)
{
	// 충돌을 하면
#ifdef _DEBUG
	float distance = GetPointDistance(_circle.mPos, _otherCircle.mPos);
	float radiusSum = _circle.mRadius + _otherCircle.mRadius;

	return distance < radiusSum;
#else
	return GetPointDistance(_circle.mPos, _otherCircle.mPos) < \
		_circle.mRadius + _otherCircle.mRadius;
#endif // _DEBUG
}

bool Geometry::IsColOfCircleToPoint(const GameCircle& _circle, const GamePos& _pointPos)
{
#ifdef _DEBUG
	float distance = GetPointDistance(_circle.mPos, _pointPos);
	float radius = _circle.mRadius;

	return distance < radius;
#else
	return GetPointDistance(_circle.mPos, _pointPos) < _circle.mRadius;
#endif // _DEBUG
}

inline float Geometry::ABS(const float _value)
{
	return (_value < 0) ? (-_value) : (_value);
}

inline float Geometry::GetPointDistance(const GamePos& _pos, const GamePos& _otherPos)
{
	float xDistance = ABS(_otherPos.mX - _pos.mX);
	float yDistance = ABS(_otherPos.mY - _pos.mY);

	return sqrtf((xDistance * xDistance) + (yDistance * yDistance));
}
