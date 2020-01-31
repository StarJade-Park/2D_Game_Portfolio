#pragma once
#include "GameShape.h"
#include "GameSize.h"

class Geometry;
class GameRectangle
	: public GameShape
{
	friend Geometry;
public:
	float Direction (PivotDirection _setPivot = PivotDirection::Left);

	GameRectangle ()
		: GameShape( )
		, mSize ({ 0.0f, 0.0f })
	{
		EMPTY_STATEMENT;
	}

	GameRectangle (PivotDirection _pivot)
		: GameShape(_pivot)
		, mSize ({ 0.0f, 0.0f })
	{
		EMPTY_STATEMENT;
	}

	GameRectangle (
		GamePos _pos,
		GameSize _size,
		PivotDirection _pivot = PivotDirection::LeftTop
	)
		: GameShape(_pos, _pivot)
		, mSize (_size)
	{
		EMPTY_STATEMENT;
	}

	~GameRectangle () = default;

#pragma region getset
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

	GamePos GetRightTop( ) const
	{
		return { GetRight( ), GetTop( ) };
	}

	GamePos GetLeftBot( ) const
	{
		return { GetLeft( ), GetBottom( ) };
	}

	GamePos GetRightBot( ) const
	{
		return GamePos(GetRight( ), GetBottom( ));
	}

	GameSize GetSize( ) const
	{
		return mSize;
	}

	void SetSize(const GameSize& _size)
	{
		mSize = _size;
	}
#pragma endregion

private:
	GameSize mSize;
};



