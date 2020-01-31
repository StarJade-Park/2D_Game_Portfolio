#pragma once
#include "DunCollider.h"
class DunPointCollider
	: public DunCollider
{
public:
	void RenderDebugInfo( ) override;
	void SetColliderData( ) override;
	bool IsCollision(DunCollider* _other) override;

	DunPointCollider( );
	~DunPointCollider( );

	GamePos GetPos( ) const
	{
		return mPos;
	}

private:
	GamePos mPos;
};

