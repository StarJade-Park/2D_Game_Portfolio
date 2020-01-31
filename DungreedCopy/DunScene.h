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
	-- void SceneUpdate( ) override; // Scene�� ������ ������ �ο��ϰ� ���� �� ����� �Լ�
	-- void RenderMgrDebugInfo( ) override; // ������ Render �Լ�
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
	// FPS, Mouse pos ���
	void PrintForDebug( );

private:
	void Progress( );
	bool PushBackActorInList(DunActor* _actor);
	void ChanageScene( );

	// Scene�� ������ ������ �ο��ϰ� ���� �� ����� �Լ�
	virtual void SceneUpdate( );

	// ������ Render �Լ�
	virtual void RenderDebugInfo( );

private:
	bool mbLoaded;
	std::list<DunActor*> mListOfActor;
	GamePos mCameraPos;
};

