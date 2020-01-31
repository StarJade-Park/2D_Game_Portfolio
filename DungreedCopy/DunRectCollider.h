#pragma once
#include <..\psklib\GameRectangle.h>

#include "DunCollider.h"
class DunRectCollider
	: public DunCollider
{
public:
	void RenderDebugInfo( ) override;
	void SetColliderData( ) override;
	bool IsCollision(DunCollider* _other) override;

	DunRectCollider( );
	~DunRectCollider( );

	const GameRectangle& GetRectangle( )
	{
		return mRectangle;
	}

private:
	GameRectangle mRectangle;
};

