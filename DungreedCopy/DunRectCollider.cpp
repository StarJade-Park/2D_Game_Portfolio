#include "DunRectCollider.h"
#include "DunCircleCollider.h"
#include "DunPointCollider.h"
#include "DunRenderManager.h"

void DunRectCollider::RenderDebugInfo( )
{
	SetColliderData( );

	Rectangle(
		DunRenderManager::GetBackDC( ),
		mRectangle.GetLeftToInt( ),
		mRectangle.GetTopToInt( ),
		mRectangle.GetRightToInt( ),
		mRectangle.GetBottomToInt( )
	);

}

void DunRectCollider::SetColliderData( )
{
	mRectangle.SetPivot(mePivot);
	mRectangle.SetPos(GetActorPos( ) + GetSubRectPos( )); //  todo 위치 확인해보기
	mRectangle.SetSize(GetSubRectSize());
}

bool DunRectCollider::IsCollision(DunCollider* _other)
{
	bool result = false;

	switch ( _other->GetColType( ) )
	{
	case DunCollider::ColliderType::None:
		CRASH_PROG;
		break;
	case DunCollider::ColliderType::Rectangle:
		result = Geometry::IsColOfRectToRect(mRectangle, ((DunRectCollider*)_other)->GetRectangle( ));
		break;
	case DunCollider::ColliderType::Circle:
		result = Geometry::IsColOfRectToCircle(mRectangle, ((DunCircleCollider*)_other)->GetCircle( ));
		break;
	case DunCollider::ColliderType::Point:
		result = Geometry::IsColOfRectToPoint(mRectangle, ((DunPointCollider*)_other)->GetPos( ));
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

DunRectCollider::DunRectCollider( )
	: mRectangle(GameRectangle(PivotDirection::Centor))
	, DunCollider(DunCollider::ColliderType::Rectangle)
{
	EMPTY_STATEMENT;
}

DunRectCollider::~DunRectCollider( )
{
	EMPTY_STATEMENT;
}
