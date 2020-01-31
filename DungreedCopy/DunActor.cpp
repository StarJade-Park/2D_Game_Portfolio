#include "DunActor.h"
#include "DunRender.h"

std::list<DunActor*> DunActor::mListOfAllActor;
std::map<std::wstring, DunActor*> DunActor::mMapOfActor;
std::set<std::wstring> DunActor::mSetOfScene;
DunActor::ActorDestroyer DunActor::mActDest;

void DunActor::PushActorWhenSceneChanging(DunScene* _scene)
{
	for ( auto& iter : mListOfAllActor )
	{
		if ( true == iter->IsExsitBySceneRef(*_scene) )
		{
			iter->RepushAllRender( ); // 클리어 후 모두 재배치
			_scene->PushBackActorInList(iter);
		}
	}
}

void DunActor::ReleaseActorMemory( )
{
	auto iterBegin = mListOfAllActor.begin( );
	const auto& iterEnd = mListOfAllActor.end( );

	for ( ; iterBegin != iterEnd;)
	{
		if ( false == (*iterBegin)->IsDied( ) )
		{
			++iterBegin;
			continue;
		}

		delete (*iterBegin);
		iterBegin = mListOfAllActor.erase(iterBegin);
	}
}

DunActor::DunActor( )
	: mPos( )
	, mCheckPos{ { }, { }, { }, { }, { }, { }, { }, { }, { } }
	, mCheckSubPos{ { }, { }, { }, { }, { }, { }, { }, { }, { } }
	, mListOfRender()
{
	EMPTY_STATEMENT;
}

DunActor::~DunActor( )
{
	for ( auto& iter : mListOfRender )
	{
		if ( nullptr != iter )
		{
			delete iter;
			iter = nullptr;
		}
	}

	for ( auto& iter : mListOfCollider )
	{
		if ( nullptr != iter )
		{
			delete iter;
			iter = nullptr;
		}
	}
}

bool DunActor::Init( )
{
	EMPTY_STATEMENT;
	return true;
}

void DunActor::Update( )
{
	EMPTY_STATEMENT;
}

void DunActor::Collide( )
{
	EMPTY_STATEMENT;
}

void DunActor::RepushAllRender( )
{
	for ( auto& iter : mListOfRender )
	{
		iter->PushToRenderMgr( );
	}
}
