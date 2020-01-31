#pragma once
#include <list>

#include <..\psklib\MapKey.h>

#include "RoomDoorData.h"

class RoomDataMap;
class DunMonster;

class RoomData
{
	friend RoomDataMap;
private:
	RoomData( );

	~RoomData( ) = default;

public:
	RoomData* NextCreateRoom( );

public:
	bool mbCreate;
	MapKey mMapKey;
	RoomDoorData mDoor;
	RoomData* mOtherRoom[RoomDoorData::DoorDir::MAX];
	std::list<DunMonster*> mAllMonster;
};