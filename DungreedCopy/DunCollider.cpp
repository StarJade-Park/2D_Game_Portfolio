#include <..\psklib\Debug.h>

#include "DunActor.h"
#include "DunCollider.h"
#include "DunCollisionManager.h"


bool DunCollider::Init(const wchar_t* _groupName, DunActor* _actor, GameSize _size)
{
	mName = _groupName;
	mActor = _actor;
	mePivot = PivotDirection::Centor;
	SetSubRectSize(_size);
	PushToColMgr( );

	return true;
}

void DunCollider::PushToColMgr( )
{
	DunCollisionManager::Instance( ).PushCollider(this);
}

void DunCollider::HandlingCollision(DunCollider* _other)
{
	if ( this == _other )
	{
		CRASH_PROG;
	}

	if ( true == IsCollision(_other) ) // �浹 ���� ����
	{
		auto findIter = mSetOfOthers.find(_other);

		if ( mSetOfOthers.end( ) == findIter ) // �浹�� �� ������
		{
			mSetOfOthers.insert(_other);
			GetActor( ).EnterCollision(this, _other);
		}
		else // �浹 �߾���
		{
			GetActor( ).StayCollision(this, _other);
		}
	}
	else // �浹 ���� ���
	{
		auto findIter = mSetOfOthers.find(_other);

		if ( mSetOfOthers.end( ) != findIter )
		{
			mSetOfOthers.erase(_other);
			GetActor( ).ExitCollision(this, _other);
		}
	}

}

DunCollider::DunCollider(ColliderType _type/* = ColliderType::None*/)
	: mColType(_type)
	, mSetOfOthers( )
{
	EMPTY_STATEMENT;
}


DunCollider::~DunCollider( )
{
}
