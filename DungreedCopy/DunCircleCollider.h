#pragma once
#include <..\psklib\Geometry.h>

#include "DunCollider.h"

class DunCircleCollider
	: public DunCollider
{
public:
	void RenderDebugInfo( ) override;
	void SetColliderData( ) override;
	bool IsCollision(DunCollider* _other) override;

	DunCircleCollider( );
	~DunCircleCollider( );

	GameCircle& GetCircle( )
	{
		return mCircle;
	}

private:
	GameCircle mCircle;
};

