#pragma once
#include <list>

#include <..\psklib\Geometry.h>

#include "DunObject.h"

class DunActor;
class DunSceneManager;
class DunRenderManager;
/*
	- virtual function list
	.public
	-- bool Loading( ) override;
	.private
	-- void SceneUpdate( ) override; // Scene에 간단한 로직을 부여하고 싶을 때 사용할 함수
	-- void RenderMgrDebugInfo( ) override; // 디버깅용 Render 함수
*/
class DunScene
	: public DunObject
{
	friend DunActor;
	friend DunSceneManager;
	friend DunRenderManager;

public:
	void Update( );
	void Render( );
	void Collision( );
	void Release( );
	bool MangerLoading( );

	virtual bool Loading( );

	bool IsLoaded( )
	{
		return mbLoaded;
	}

	GamePos GetCameraPos( ) const
	{
		return mCameraPos;
	}

	void SetCameraPos(const GamePos& _pos)
	{
		mCameraPos = _pos;
	}

protected:
	DunScene( );
	virtual ~DunScene( ) = 0;
	// FPS, Mouse pos 출력
	void PrintForDebug( );

private:
	void Progress( );
	bool PushBackActorInList(DunActor* _actor);
	void ChanageScene( );

	// Scene에 간단한 로직을 부여하고 싶을 때 사용할 함수
	virtual void SceneUpdate( );

	// 디버깅용 Render 함수
	virtual void RenderDebugInfo( );

private:
	bool mbLoaded;
	std::list<DunActor*> mListOfActor;
	GamePos mCameraPos;
};

