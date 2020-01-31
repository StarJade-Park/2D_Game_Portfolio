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
	void SceneUpdate( ) override; // Scene�� ������ ������ �ο��ϰ� ���� �� ����� �Լ�
	void RenderDebugInfo( ) override; // ������ Render �Լ�
	void LoadRoomData();

private:
	static int MaxCounterRoom;
	GameSoundPlayer* mBgm;

	RoomData* mCurRoom;
	DunRoom* mDunRoom;
	//DunMonster* testMonster;
};

