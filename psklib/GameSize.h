#pragma once
#include "Vector2D.h"

class GameSize
	: public Vector2D
{
public:
	GameSize ()
		: Vector2D ()
	{
		EMPTY_STATEMENT;
	}

	GameSize (float _x, float _y)
		: Vector2D (_x, _y)
	{
		EMPTY_STATEMENT;
	}

	~GameSize () = default;

	void Reverse (void)
	{
		mX = -mX;
		mY = -mY;
	}

	GameSize& operator+=(const GameSize& _other)
	{
		mX += _other.mX;
		mY += _other.mY;

		return *this;
	}

	GameSize& operator-=(const GameSize& _other)
	{
		mX -= _other.mX;
		mY -= _other.mY;

		return *this;
	}

	// - ½ºÄ®¶ó °ö ¿¬»êÀÚ
	GameSize& operator*=(const float _scala)
	{
		mX *= _scala;
		mY *= _scala;

		return *this;
	}

	GameSize& operator/=(const float _scala)
	{
		mX /= _scala;
		mY /= _scala;

		return *this;
	}

	// - ¿ª¹æÇâ ¿¬»êÀÚ
	GameSize operator-()
	{
		return GameSize (-mX, -mY);
	}

	// - »¬¼À
	GameSize operator-(const GameSize& _other)
	{
		return GameSize (mX - _other.mX, mY - _other.mY);
	}

	// - ½ºÄ®¶ó °ö
	GameSize operator*(const float _scala)
	{
		return GameSize (mX * _scala, mY * _scala);
	}

	GameSize& operator=(const GameSize& _other)
	{
		mX = _other.mX;
		mY = _other.mY;

		return *this;
	}
};
