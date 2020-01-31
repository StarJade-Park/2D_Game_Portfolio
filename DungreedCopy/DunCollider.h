#pragma once
#include <set>

#include <..\psklib\GameSize.h>

#include "DunSubActor.h"
#include "DunObjectAbility.h"

/*
- override function list
-- void RenderMgrDebugInfo( ) override;
-- void SetColliderData( ) override;
-- bool IsCollision(DunCollider* _other) override;
*/
class DunCollider
	: public DunSubActor, public DunObjectAbility
{
	friend class DunCollisionManager;
	friend class DunActor;
public:
	// - type list : None, Rectangle, Circle, Point, MAX
	enum class ColliderType
	{
		None, Rectangle, Circle, Point, MAX
	};

public:
	virtual void RenderDebugInfo( ) = 0;
	virtual void SetColliderData( ) = 0;
	virtual bool IsCollision(DunCollider* _other) = 0;

	ColliderType GetColType( )
	{
		return mColType;
	}

	// - GetName과 같음
	// - 그룹이라는 것을 명확하게 만들기 위해 만든 함수
	const wchar_t* GetGroupName( )
	{
		return mName.c_str( );
	}

	bool Init(const wchar_t* _groupName, DunActor* _actor, GameSize _size = { 10.0f, 10.0f });
	void PushToColMgr( );
	// - 충돌 처리
	void HandlingCollision(DunCollider* _other);

protected:
	// - defualt : ColliderType::None
	DunCollider(ColliderType _type = ColliderType::None);
	virtual ~DunCollider( );

protected:
	// mName std::wstring m_GroupName;
	ColliderType mColType;
	std::set<DunCollider*> mSetOfOthers;
};

