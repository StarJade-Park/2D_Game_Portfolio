#include <Windows.h>

#include <..\psklib\Debug.h>

#include "DunCollisionManager.h"
#include "DunCollider.h"

bool DunCollisionManager::IsLinked(const wchar_t* _left, const wchar_t* _right)
{
	std::wstring left = _left;
	std::wstring right = _right;

	return (mMapOfLinkData.end( )) == mMapOfLinkData.find(left + right) \
			&& (mMapOfLinkData.end( )) == mMapOfLinkData.find(right + left);
}

void DunCollisionManager::SetLink(const wchar_t* _left, const wchar_t* _right)
{
	if ( false == IsLinked(_left, _right) )
	{
		CRASH_PROG;
	}

	const auto& colGroupIterLeft = mMapOfColList.find(_left);
	if ( mMapOfColList.end( ) == colGroupIterLeft )
	{
		mMapOfColList.insert(
			std::map<std::wstring, std::list<DunCollider*>>::value_type(
				_left, std::list<DunCollider*>( )
			)
		);
	}

	const auto& colGroupIterRight = mMapOfColList.find(_right);
	if ( mMapOfColList.end( ) == colGroupIterRight )
	{
		mMapOfColList.insert(
			std::map<std::wstring, std::list<DunCollider*>>::value_type(
				_right, std::list<DunCollider*>( )
			)
		);
	}

	LinkData data;
	data.leftName = _left;
	data.rightName = _right;
	mMapOfLinkData.insert(
		std::map<std::wstring, LinkData>::value_type(data.leftName + data.rightName, data)
	);
}

void DunCollisionManager::Release( )
{
	auto colStart = mMapOfColList.begin( );
	const auto& colEnd = mMapOfColList.end( );
	for ( ; colStart != colEnd; ++colStart )
	{
		auto colSecondStart = colStart->second.begin( );
		const auto& colSecondEnd = colStart->second.end( );
		for ( ; colSecondStart != colSecondEnd; )
		{
			if ( false == (*colSecondStart)->IsDied( ) )
			{
				++colSecondStart;
				continue;
			}

			colSecondStart = colStart->second.erase(colSecondStart);
		}
	}
}

void DunCollisionManager::RenderDebugInfo( )
{
	for ( auto& mapIter : mMapOfColList )
	{
		for ( auto& listIter : mapIter.second/* collider list */ )
		{
			if ( false == listIter->IsCanUpdate( ) )
			{
				continue;
			}
			listIter->RenderDebugInfo( );
		}
	}
}

void DunCollisionManager::ClearAllCollider( )
{
	for (auto& ListOfCol : mMapOfColList )
	{
		ListOfCol.second.clear( );
	}
}

void DunCollisionManager::CollideGroupToGroup(const wchar_t* _left, const wchar_t* _right)
{
	const auto& LeftGroup = mMapOfColList.find(_left);
	const auto& RightGroup = mMapOfColList.find(_right);

	if ( LeftGroup == mMapOfColList.end( ) )
	{
		CRASH_PROG;
		return;
	}

	if ( RightGroup == mMapOfColList.end( ) )
	{
		CRASH_PROG;
		return;
	}

	if ( 0 >= LeftGroup->second.size( ) )
	{
		OutputDebugStringW(L"Col LeftGroup Size : 0");
		return;
	}

	if ( 0 >= RightGroup->second.size( ) )
	{
		OutputDebugStringW(L"Col RightGroup Size : 0");
		return;
	}

	for ( auto& LIter : LeftGroup->second )
	{
		if ( false == LIter->IsCanUpdate( ) )
		{
			continue;
		}

		LIter->SetColliderData( );

		// 이미 handling한 collision 또 하는 거 방지
		for ( auto& RIter : RightGroup->second )
		{
			if ( false == RIter->IsCanUpdate( ) )
			{
				RIter->SetColliderData( );
				LIter->HandlingCollision(RIter);
			}
		}
	}
}

// TODO: 같은 그룹 충돌 처리
void DunCollisionManager::CollideGroupSelf(const wchar_t* _thisName)
{
	CRASH_PROG;
	const auto& group = mMapOfColList.find(_thisName);
	for ( auto& iter : group->second )
	{
		if ( false == iter->IsCanUpdate( ) )
		{
			continue;
		}

		iter->SetColliderData( );
		iter->HandlingCollision(iter);
	}
}

void DunCollisionManager::PushCollider(DunCollider* _col)
{
	auto colGroupIter = mMapOfColList.find(_col->GetGroupName( ));

	if ( mMapOfColList.end( ) == colGroupIter )
	{
		mMapOfColList.insert(
			std::map<std::wstring, std::list<DunCollider*>>::value_type(
				_col->GetGroupName( ), std::list<DunCollider*>( )
			)
		);

		colGroupIter = mMapOfColList.find(_col->GetGroupName( ));
	}

	colGroupIter->second.push_back(_col);
}

void DunCollisionManager::Collide( )
{
	for ( auto& linkIter : mMapOfLinkData)
	{
		if ( linkIter.second.leftName != linkIter.second.rightName )
		{
			CollideGroupToGroup(linkIter.second.leftName.c_str( ), linkIter.second.rightName.c_str( ));
		}
		else
		{
			CollideGroupSelf(linkIter.second.leftName.c_str( ));
		}
	}
}
