#pragma once
#include <list>
#include <map>
#include <set>
#include <string>

#include <..\psklib\Geometry.h>
#include <..\psklib\Debug.h>

#include "DunScene.h"
#include "DunSceneManager.h"
#include "DunCollider.h"

class DunRender;

/*
- virtual function list
-- bool Init( ) override;
-- void Update( ) override;
-- void Collide( ) override;

-- void EnterCollision(DunCollider* _left, DunCollider* _right) override;
-- void StayCollision(DunCollider* _left, DunCollider* _right) override;
-- void ExitCollision(DunCollider* _left, DunCollider* _right) override;
*/
class DunActor
	: public DunObject
{
	friend DunScene;
public:
	enum _ActorCheckDir
	{
		Left, Right, Top, Bottom, Ground, LT, LB, RT, RB, MAX
	};

public:
	static void PushActorWhenSceneChanging(DunScene* _scene);
	static void ReleaseActorMemory( );

	virtual void EnterCollision(DunCollider* _left, DunCollider* _right)
	{
		_left;
		_right;
	}

	virtual void StayCollision(DunCollider* _left, DunCollider* _right)
	{
		_left;
		_right;
	}

	virtual void ExitCollision(DunCollider* _left, DunCollider* _right)
	{
		_left;
		_right;
	}

	GamePos GetPos( ) const
	{
		return mPos;
	}
	
	void SetPos(const GamePos& _pos)
	{
		mPos = _pos;
	}

	void SetXPos(const float _x)
	{
		mPos.mX = _x;
	}

	void SetYPos(const float _y)
	{
		mPos.mY = _y;
	}

	GamePos GetCheckedPos(_ActorCheckDir _dir)
	{
		return mPos + mCheckPos[_dir];
	}

#pragma region create_actor
	template<typename Type>
	static Type* CreateActor(const wchar_t* _name = L"", bool _bFindAble = false)
	{
		Type* newActor = new Type( );
		newActor->SetName(_name);

		mListOfAllActor.push_back(newActor);

		if ( nullptr != DunSceneManager::Instance( ).GetCreateSceneOrNull( ) )
		{
			newActor->mSetOfScene.insert(
				DunSceneManager::Instance( ).GetCreateSceneOrNull( )->GetName( )
			);
			DunSceneManager::Instance( ). \
				GetCreateSceneOrNull( )->PushBackActorInList(newActor);
		}
		else if ( nullptr != DunSceneManager::Instance( ).GetCurSceneOrNull( ) )
		{
			newActor->mSetOfScene.insert(
				DunSceneManager::Instance( ).GetCurSceneOrNull( )->GetName( )
			);
			DunSceneManager::Instance( ). \
				GetCurSceneOrNull( )->PushBackActorInList(newActor);
		}

		if ( true == _bFindAble )
		{
			mMapOfActor.insert(
				std::map<std::wstring, DunActor*>::value_type(_name, newActor)
			);
		}
		newActor->Init( );

		return newActor;
	}
#pragma endregion

#pragma region find_actor
	static DunActor* FindActorOrNull(const wchar_t* _actorName)
	{
		const auto& findIter = mMapOfActor.find(_actorName);

		if ( mMapOfActor.end( ) == findIter )
		{
			return nullptr;
		}

		return findIter->second;
	}
#pragma endregion

#pragma region create_render
	template<typename Type>
	Type* CreateRender(int _order = 0)
	{
		Type* newRender = new Type( );
		newRender->Init(_order, this);
		mListOfRender.push_back(newRender);

		return newRender;
	}
#pragma endregion

#pragma region create_collider
	template<typename Type>
	Type* CreateCollider(const wchar_t* _groupName = L"Default", GameSize _size = { 10.f, 10.f })
	{
		Type* newCol = new Type( );
		newCol->Init(_groupName, this, _size);

		mListOfCollider.push_back(newCol);

		return newCol;
	}
#pragma endregion

#pragma region insert_to_sceneset
	template<typename ...Type>
	void InsertActorToScene(const wchar_t* _sceneName, Type ..._args)
	{
		// size_t argsSize = sizeof...(_args);

		if ( false == IsExsitByNameChPtr(_sceneName) )
		{
			mSetOfScene.insert(_sceneName);
		}

		InsertActorToScene(_args...);
	}

private:
	void InsertActorToScene( )
	{
		EMPTY_STATEMENT;
	}
#pragma endregion

protected:
	DunActor( );
	virtual ~DunActor( ) = 0;

private:
	virtual bool Init( );
	virtual void Update( );
	virtual void Collide( );

	bool IsExsitBySceneRef(const DunScene& _scene) const
	{
		return IsExsitByNameStr(_scene.GetName( ));
	}

	bool IsExsitByNameStr(const std::wstring& _name) const
	{
		return mSetOfScene.end( ) != mSetOfScene.find(_name);
	}

	bool IsExsitByNameChPtr(const wchar_t* _name) const
	{
		return mSetOfScene.end( ) != mSetOfScene.find(_name);
	}

	void RepushAllRender();

#pragma region ActorDestroyer
	class ActorDestroyer
	{
	public:
		ActorDestroyer( ) = default;

		~ActorDestroyer( )
		{
			DunActor::DestructActor( );
		}
	};
	friend ActorDestroyer;

	static void DestructActor( )
	{
		for ( auto& iter : mListOfAllActor )
		{
			delete iter;
			iter = nullptr;
		}
	}
#pragma endregion

protected:
	GamePos mPos;
	GamePos mCheckPos[_ActorCheckDir::MAX];
	GamePos mCheckSubPos[_ActorCheckDir::MAX];

	static std::list<DunActor*> mListOfAllActor;

	// 특정 Actor 찾기 쉬움
	// Scene을 구분하지 않고 Obj Control 가능
	static std::map<std::wstring, DunActor*> mMapOfActor;

	// SceneCheck
	static std::set<std::wstring> mSetOfScene;

	// 소멸자용 멤버 클래스
	static ActorDestroyer mActDest;

	std::list<DunRender*> mListOfRender;
	std::list<DunCollider*> mListOfCollider;
};

