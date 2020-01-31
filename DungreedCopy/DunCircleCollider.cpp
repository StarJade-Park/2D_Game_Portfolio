#include <..\psklib\Debug.h>

#include "DunCircleCollider.h"
#include "DunRenderManager.h"
#include "DunRectCollider.h"
#include "DunPointCollider.h"

void DunCircleCollider::RenderDebugInfo( )
{
	Ellipse(
		DunRenderManager::GetBackDC( ),
		GetActorPos( ).ToInt( ).mX - GetSubRectSize( ).XToInt( ),
		GetActorPos( ).ToInt( ).mY - GetSubRectSize( ).YToInt( ),
		GetActorPos( ).ToInt( ).mX + GetSubRectSize( ).XToInt( ),
		GetActorPos( ).ToInt( ).mY + GetSubRectSize( ).YToInt( )
	);
}

void DunCircleCollider::SetColliderData( )
{
	mCircle.SetPos(GetActorPos( ));
	mCircle.SetRadius(GetSubRectSize( ).mX);
}

// - Downcasting 사용되는 함수
bool DunCircleCollider::IsCollision(DunCollider * _other)
{
	bool result = false;

	switch ( _other->GetColType( ) )
	{
	case DunCollider::ColliderType::None:
		CRASH_PROG;
		break;
	case DunCollider::ColliderType::Rectangle:
		result = Geometry::IsColOfRectToCircle(((DunRectCollider*)_other)->GetRectangle( ), mCircle);
		break;
	case DunCollider::ColliderType::Circle:
		result = Geometry::IsColOfCircleToCircle(((DunCircleCollider*)_other)->GetCircle( ), mCircle);
		break;
	case DunCollider::ColliderType::Point:
		result = Geometry::IsColOfCircleToPoint(mCircle, ((DunPointCollider*)_other)->GetPos( ));
		break;
	case DunCollider::ColliderType::MAX:
		CRASH_PROG;
		break;
	default:
		CRASH_PROG;
		break;
	}

	return result;
}

DunCircleCollider::DunCircleCollider( )
	: mCircle(0.0f)
	, DunCollider(DunCollider::ColliderType::Circle)
{
	EMPTY_STATEMENT;
}

DunCircleCollider::~DunCircleCollider( )
{
	EMPTY_STATEMENT;
}
