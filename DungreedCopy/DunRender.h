#pragma once
#pragma comment (lib, "msimg32.lib") // Windows에서 지원하는 라이브러리를 쓰겠다는 것

#include <..\psklib\Geometry.h>

#include "DunObject.h"
#include "DunSubActor.h"
#include "DunActor.h"

class DunRender
	: public DunSubActor
{
	friend DunActor;
	friend class DunRenderManger;
public:
	virtual bool Init(int _val, DunActor* _actor);
	virtual void Render( ) = 0;
	virtual void RenderDebugInfo( );

#pragma region getset
	inline int GetOrder( ) const
	{
		return mOrderIndex;
	}

	inline void SetOrder(int _order)
	{
		mOrderIndex = _order;
	}

	inline DunActor& GetActor( ) const
	{
		return *mActor;
	}

	// - Set actor pos by camera effect flag
	inline GamePos SetActorPosByFlag( );
#pragma endregion

protected:
	DunRender( );
	~DunRender( ) = default;

private:
	bool PushToRenderMgr( );

private:
	int mOrderIndex;
};

