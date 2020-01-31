#pragma once
#include <map>

#include "DunScene.h"
#include "DunRoom.h"

class DungreedStage_01
	: public DunScene
{
public:
	DungreedStage_01 ();
	~DungreedStage_01 ();

	void CreateRooms(int _maxCreation);
	
	void SetStartRoom(DunRoom* _start)
	{
		mStartRoom = _start;
	}

	DunRoom& GetStartRoom( ) const
	{
		return *mStartRoom;
	}

	DunRoom& GetCurRoom( ) const
	{
		return *mCurRoom;
	}

private:
	//void SceneUpdate( ) override;
	//void RenderMgrDebugInfo( ) override;

private:
	DunRoom* mStartRoom;
	DunRoom* mCurRoom;
	std::map<int, DunRoom*> mMapOfRoom;
};

