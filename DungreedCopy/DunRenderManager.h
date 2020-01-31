#pragma once
#include <map>
#include <set>
#include <list>

#include "DunRender.h"
#include "DunImage.h"

class DunRenderManager
{
	friend class GameScene;
	friend class GameCore;
	friend class DunScene;
public:
#pragma region singleton
	static DunRenderManager& Instance( )
	{
		static DunRenderManager mInstance;
		return mInstance;
	}
#pragma endregion

	static HDC GetBackDC( )
	{
		return mBackImgBuffer->GetImgDC( );
	}

	void Render( );
	void Release( );
	bool PushRenderToMgr(DunRender* _render);

	static void OnDebugRender( )
	{
		mbDebugFlag = true;
	}

	static void OffDebugRender( )
	{
		mbDebugFlag = false;
	}

	static void SwitchDebugRender( )
	{
		mbDebugFlag = !mbDebugFlag;
	}

private:
	DunRenderManager( )
	{
		Init( );
	}

	~DunRenderManager( );
	void ClearAllRender( );
	void Init( );
	void RenderMgrDebugInfo( );

private:
	static DunImage* mBackImgBuffer;
	std::map<int, std::list<DunRender*>> mRenderMap;
	std::set<int> mYSort;

	static bool mbDebugFlag;
};

