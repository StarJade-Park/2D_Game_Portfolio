#include <..\psklib\Debug.h>

#include "DunImgRender.h"
#include "DungreedCore.h"
#include "DunResourceManager.h"
#include "DunRenderManager.h"
#include "DunImage.h"
#include "DunActor.h"


DunImgRender::DunImgRender( )
	: mImage(nullptr)
{
}

void DunImgRender::SetImage(const wchar_t* _imgName)
{
	mImage = DunResourceManager::FindImageOrNull(_imgName);

	if ( nullptr == mImage )
	{
		CRASH_PROG;
	}
}

void DunImgRender::Render( )
{
	if ( nullptr == mImage )
	{
		CRASH_PROG;
	}

	BitBlt(
		DunRenderManager::Instance( ).GetBackDC( ),
		GetActorPos( ).ToInt( ).mX,
		GetActorPos( ).ToInt( ).mY,
		45,
		57,
		mImage->GetImgDC( ),
		79,
		123,
		SRCCOPY
	);
}
