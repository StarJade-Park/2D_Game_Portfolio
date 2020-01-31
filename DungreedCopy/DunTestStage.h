#pragma once
#include <map>
#include "DunScene.h"

class GameSoundPlayer;
class DunRoom;
class RoomData;
class DunPlayer;
class DunMonster;

class DunTestStage
	: public DunScene
{
public:
	DunTestStage( );
	~DunTestStage( );

	bool Loading( ) override;

private:
	void SceneUpdate( ) override; // Scene에 간단한 로직을 부여하고 싶을 때 사용할 함수
	void RenderDebugInfo( ) override; // 디버깅용 Render 함수
	void LoadRoomData();

private:
	static int MaxCounterRoom;
	GameSoundPlayer* mBgm;

	RoomData* mCurRoom;
	DunRoom* mDunRoom;
	//DunMonster* testMonster;
};

