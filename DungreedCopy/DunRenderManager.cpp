#include <..\psklib\tags.h>

#include "DunRenderManager.h"
#include "DunSceneManager.h"
#include "DunCollisionManager.h"
#include "DungreedCore.h"
#include "DunScene.h"
#include "DunRender.h"

DunImage* DunRenderManager::mBackImgBuffer = nullptr;
bool DunRenderManager::mbDebugFlag = false;

void DunRenderManager::Render( )
{
	Rectangle(
		DunRenderManager::GetBackDC( ),
		0,
		0,
		def::__tag::width,
		def::__tag::height
	);

	for ( auto& mapIter : mRenderMap )
	{
		for ( auto& listIter : mapIter.second )
		{
			listIter->Render( );
		}
	}

	if ( nullptr != DunSceneManager::Instance( ).GetCurSceneOrNull( ) && \
		true == mbDebugFlag )
	{
		RenderMgrDebugInfo( );
		DunCollisionManager::Instance( ).RenderDebugInfo( );
		DunSceneManager::Instance( ).GetCurSceneOrNull( )->RenderDebugInfo( );
	}

	BitBlt(
		DungreedCore::MainWindow( ).GetHDC( ),
		0,
		0,
		DungreedCore::MainWindow( ).GetWndSize( ).ToInt( ).mX,
		DungreedCore::MainWindow( ).GetWndSize( ).ToInt( ).mY,
		DunRenderManager::GetBackDC( ),
		0,
		0,
		SRCCOPY
	);
}

void DunRenderManager::Release( )
{
	for ( auto& mapIter : mRenderMap )
	{
		auto iter = mapIter.second.begin( );
		const auto& ListEnd = mapIter.second.end( );
		for ( ; iter != ListEnd; )
		{
			if ( false == (*iter)->IsDied( ) )
			{
				++iter;
				continue;
			}

			iter = mapIter.second.erase(iter);
		}
	}
}

bool DunRenderManager::PushRenderToMgr(DunRender * _render)
{
	auto findIter = mRenderMap.find(_render->GetOrder( ));

	if ( mRenderMap.end( ) == findIter )
	{
		mRenderMap.insert(
			std::map<int, std::list<DunRender*>>::value_type(
				_render->GetOrder( ), std::list<DunRender*>( )
			)
		);

		findIter = mRenderMap.find(_render->GetOrder( ));
	}

	findIter->second.push_back(_render);
	return true;
}

DunRenderManager::~DunRenderManager( )
{
	delete mBackImgBuffer;
}

void DunRenderManager::ClearAllRender( )
{
	for ( auto& iter : mRenderMap )
	{
		iter.second.clear( );
	}
}

void DunRenderManager::Init( )
{
	mBackImgBuffer = new DunImage( );
	mBackImgBuffer->Create(DungreedCore::MainWindow( ).GetWndSize( ));
}

void DunRenderManager::RenderMgrDebugInfo( )
{
	for ( auto& mapIter : mRenderMap )
	{
		for ( auto& listIter : mapIter.second )
		{
			listIter->RenderDebugInfo( );
		}
	}
}
