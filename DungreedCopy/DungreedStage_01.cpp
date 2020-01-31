#include <Windows.h>

#include "DunRenderManager.h"
#include "DungreedStage_01.h"
#include "DunPlayer.h"

DunPlayer* player = nullptr;

DungreedStage_01::DungreedStage_01 ()
	: mCurRoom(nullptr)
	, mStartRoom(nullptr)
{
	EMPTY_STATEMENT;
}

DungreedStage_01::~DungreedStage_01 ()
{
	EMPTY_STATEMENT;
}
