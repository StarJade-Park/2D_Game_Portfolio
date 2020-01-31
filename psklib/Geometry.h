#pragma once

//#include "Vector2D.h"
#include "GamePos.h"
#include "GameSize.h"
#include "GameRectangle.h"
#include "GameCircle.h"

class Geometry
{
private:
	Geometry( ) = delete;
	~Geometry( ) = delete;

public:
	static bool IsColOfRectToPoint(const GameRectangle& _rect, const GamePos& _pos);
	static bool IsColOfRectToRect(const GameRectangle&	_rect, const GameRectangle& _otherRect);
	static bool IsColOfRectToCircle(const GameRectangle& _rect, const GameCircle& _circle);

	static bool IsColOfCircleToCircle(const GameCircle& _circle, const GameCircle& _otherCircle);
	static bool IsColOfCircleToPoint(const GameCircle&	_circle, const GamePos& _pos);

	inline static float ABS(const float _value);
	inline static float GetPointDistance(const GamePos& _pos, const GamePos& _otherPos);

public:
	static const GamePos ZeroPos;
	static const GamePos RightDirPos;
	static const GamePos LeftDirPos;
	static const GamePos TopDirPos;
	static const GamePos BottomDirPos;
	static const GameSize ZeroSize;
	static const GamePos CorrectionValue;
	static const GamePos MouseVal;

private:
	static GameRectangle mHorizonRect;
	static GameRectangle mVerticalRect;
};
