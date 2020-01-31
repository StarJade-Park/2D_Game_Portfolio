#pragma once
#include <vector>

#include <..\psklib\Geometry.h>
#include <..\psklib\Debug.h>

#include "DunImage.h"

class DunSprite
{
	friend class GameResourceManager;
public:
	DunSprite(DunImage* _img);
	~DunSprite( ) = default;
#pragma region getset
	size_t GetSpriteCount( ) const
	{
		return mSpriteRect.size( );
	}

	bool IsMultiple( )
	{
		return (1 < mSpriteRect.size( ));
	}

	GameRectangle GetSpriteRectByIndex(size_t _index = 0)
	{
		if ( 0 >= mSpriteRect.size( ) )
		{
			CRASH_PROG;
			return GameRectangle( );
		}

		return mSpriteRect[_index];
	}

	DunImage& GetImage( ) const
	{
		return *mImage;
	}

	GameRectangle operator[](int _index)
	{
		if ( 0 >= mSpriteRect.size( ) )
		{
			CRASH_PROG;
		}

		return mSpriteRect[_index];
	}

	GameRectangle at(int _index)
	{
		if ( 0 >= mSpriteRect.size( ) )
		{
			CRASH_PROG;
		}

		return mSpriteRect[_index];
	}

	GameRectangle GetSpriteRectByIndex(int _index)
	{
		return at(_index);
	}

	GameColor PosToColor(GamePos _pos)
	{
		return mImage->PosToColor(_pos);
	}

#pragma endregion
	void CutImage(int _x, int _y);

private:
	DunImage* mImage;
	std::vector<GameRectangle> mSpriteRect;
};

