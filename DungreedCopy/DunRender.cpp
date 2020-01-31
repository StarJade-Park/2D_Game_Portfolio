#include "DunRender.h"
#include "DunSceneManager.h"
#include "DunRenderManager.h"

bool DunRender::Init(int _val, DunActor* _actor)
{
	mOrderIndex = _val;
	mActor = _actor;
	return PushToRenderMgr( );
}

void DunRender::RenderDebugInfo( )
{
	Rectangle(
		DunRenderManager::GetBackDC( ),
		CalcPivotPos( ).XToInt( ) - 5,
		CalcPivotPos( ).YToInt( ) - 5,
		CalcPivotPos( ).XToInt( ) + 5,
		CalcPivotPos( ).YToInt( ) + 5
	);
}

GamePos DunRender::SetActorPosByFlag( )
{
	if ( false == mbCameraEffect )
	{
		return mActor->GetPos( );
	}
	else
	{
		return mActor->GetPos( ) - \
			DunSceneManager::Instance( ).GetCurSceneOrNull( )->GetCameraPos( );
	}
}

DunRender::DunRender( )
	: DunSubActor( )
	, mOrderIndex(def::__tag::InvalidValue)
{
	EMPTY_STATEMENT;
}

bool DunRender::PushToRenderMgr( )
{
	return DunRenderManager::Instance( ).PushRenderToMgr(this);
}
