#pragma once
#include "GameShape.h"

class Geometry;
class GameCircle
	: public GameShape
{
	friend Geometry;
public:
	GameCircle(float _radius)
		: GameShape( )
		, mRadius(_radius)
	{
		EMPTY_STATEMENT;
	}

	~GameCircle( ) = default;

	GameCircle& operator=(const GameCircle& _other)
	{
		mePivot = _other.mePivot;
		mRadius = _other.mRadius;
		mPos = _other.mPos;

		return *this;
	}

#pragma region getset
	float GetRadius( ) const
	{
		return mRadius;
	}

	void SetRadius(const float _radius)
	{
		mRadius = _radius;
	}

	float GetLeft( ) const;
	float GetRight( ) const;
	float GetTop( ) const;
	float GetBottom( ) const;

	int GetLeftToInt( )
	{
		return (int)GetLeft( );
	};

	int GetRightToInt( )
	{
		return (int)GetRight( );
	};

	int GetTopToInt( )
	{
		return (int)GetTop( );
	};

	int GetBottomToInt( )
	{
		return (int)GetBottom( );
	};

	GamePos GetLeftTop( ) const
	{
		return { GetLeft( ), GetTop( ) };
	}

	GamePos RightTop( )	const
	{
		return { GetRight( ), GetTop( ) };
	}

	GamePos LeftBot( )	const
	{
		return { GetLeft( ), GetBottom( ) };
	}

	GamePos RightBot( )	const
	{
		return GamePos(GetRight( ), GetBottom( ));
	}
#pragma endregion

private:
	float mRadius;
};

