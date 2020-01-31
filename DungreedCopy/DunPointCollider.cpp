#include <..\psklib\Debug.h>

#include "DunPointCollider.h"
#include "DunCircleCollider.h"
#include "DunRectCollider.h"
#include "DunRenderManager.h"

void DunPointCollider::RenderDebugInfo( )
{
	//if ( true == DebugFlag::Instance( ).IsFlagSet( ) )
	//{
		Ellipse(
			DunRenderManager::GetBackDC( ),
			GetActorPos( ).ToInt( ).mX -3,
			GetActorPos( ).ToInt( ).mY -3,
			GetActorPos( ).ToInt( ).mX +3,
			GetActorPos( ).ToInt( ).mY +3
		);
	//}
}

void DunPointCollider::SetColliderData( )
{
	mPos = GetActorPos( );
}

bool DunPointCollider::IsCollision(DunCollider * _other)
{
	bool result = false;

	switch ( _other->GetColType( ) )
	{
	case DunCollider::ColliderType::None:
		CRASH_PROG;
		break;
	case DunCollider::ColliderType::Rectangle:
		result = Geometry::IsColOfRectToPoint(((DunRectCollider*)_other)->GetRectangle( ), mPos);
		break;
	case DunCollider::ColliderType::Circle:
		result = Geometry::IsColOfCircleToPoint(((DunCircleCollider*)_other)->GetCircle( ), mPos);
		break;
	case DunCollider::ColliderType::Point:
		result = (mPos == ((DunPointCollider*)_other)->mPos);
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

DunPointCollider::DunPointCollider( )
	: mPos(GamePos( ))
	, DunCollider(DunCollider::ColliderType::Point)
{
	EMPTY_STATEMENT;
}

DunPointCollider::~DunPointCollider( )
{
	EMPTY_STATEMENT;
}
