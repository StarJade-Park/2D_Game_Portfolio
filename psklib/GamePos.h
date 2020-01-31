#pragma once
#include "Vector2D.h"

class GamePos
	: public Vector2D
{
public:
	GamePos ()
		: Vector2D()
	{
		EMPTY_STATEMENT;
	}

	GamePos (float _x, float _y)
		: Vector2D (_x, _y)
	{
		EMPTY_STATEMENT;
	}

	~GamePos () = default;

	// - 방향을 반대로 가리키게 하는 함수
	void Reverse (void)
	{
		mX = -mX;
		mY = -mY;
	}

	GamePos operator+(const GamePos& _other)
	{
		return GamePos (mX + _other.mX, mY + _other.mY);
	}

	GamePos& operator+=(const GamePos& _other)
	{
		mX += _other.mX;
		mY += _other.mY;

		return *this;
	}

	GamePos& operator-=(const GamePos& _other)
	{
		mX -= _other.mX;
		mY -= _other.mY;

		return *this;
	}

	// - 스칼라 곱 연산자
	GamePos& operator*=(const float _scala)
	{
		mX *= _scala;
		mY *= _scala;

		return *this;
	}

	GamePos& operator/=(const float _scala)
	{
		mX /= _scala;
		mY /= _scala;

		return *this;
	}

	// - 역방향 연산자
	GamePos operator-()
	{
		return GamePos (-mX, -mY);
	}

	// - 뺄셈
	GamePos operator-(const GamePos& _other)
	{
		return GamePos (mX - _other.mX, mY - _other.mY);
	}

	// - 스칼라 곱
	GamePos operator*(const float _scala)
	{
		return GamePos (mX * _scala, mY * _scala);
	}

	GamePos operator*(const GamePos _other)
	{
		return GamePos(mX * _other.mX, mY * _other.mY);
	}

	GamePos& operator=(const GamePos& _other)
	{
		mX = _other.mX;
		mY = _other.mY;

		return *this;
	}

	bool operator==(const GamePos& _other)
	{
		return (mX == _other.mX &&
				mY == _other.mY);
	}

	GamePos abs( )
	{
		GamePos absPos = *this;
		if ( 0 > absPos.mX )
		{
			absPos.mX = -absPos.mX;
		}

		if ( 0 > absPos.mY )
		{
			absPos.mY = absPos.mY;
		}

		return absPos;
	}
};
