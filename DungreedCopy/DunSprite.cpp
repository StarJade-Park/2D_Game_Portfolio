#include "DunSprite.h"

DunSprite::DunSprite(DunImage* _img)
	: mImage(_img)
{
}

void DunSprite::CutImage(int _x, int _y)
{
	GameSize size = {
		mImage->GetSize( ).mX / (float)_x,
		mImage->GetSize( ).mY / (float)_y
	};

	GameRectangle rt;
	GamePos pos = Geometry::ZeroPos;

	for ( int y = 0; y < _y; ++y )
	{
		for ( int x = 0; x < _x; ++x )
		{
			rt.SetPos(pos);
			rt.SetSize(size);
			mSpriteRect.push_back(rt);
			pos.mX += size.mX;
		}

		pos.mY += size.mY;
		pos.mX = 0.0f;
	}
}
