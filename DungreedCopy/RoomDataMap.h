#pragma once
#include <vector>
#include <map>
#include <list>

#include "RoomDoorData.h"
#include "RoomData.h"

class DunActor;

/*
******* static class *******
- 다음 순서로 호출할 것
-- Init (path, img init 완료 후)
-- CreateRandomDun
-- ClearCurMap
*/
class RoomDataMap
{
public:
	enum _MapTag
	{
		Start = 0,
	};
public:
	static void Init( );
	static RoomData* CreateRandomDun(int _count = 2);
	// open data 막기
	static void CloseNullDoor();

	static void ClearCurMap( );

	static RoomDoorData FindOpenRoom(RoomDoorData::DoorDir _dir, int _Count);
	static std::vector<DunImage*>& GetAllImg( )
	{
		return mVectorOfAllImg;
	}

private:
	RoomDataMap( ) = default;
	~RoomDataMap( ) = default;
	static void DataImgLoad( );

public:
	// LTRB 정보만 가지고 있는것.
	static std::vector<RoomDoorData> mVectorOfOpenData;
	static std::vector<std::list<RoomDoorData>> mVectorOfListOpenData;

	// 방향 별로 방의 데이터를 가지고 있음
	static std::map<int, std::list<RoomDoorData>> mMapOfListOpenData;
	static RoomData* mCurMapStart;
	static std::map<__int64, RoomData*> mMapOfCurMap;

private:
	static std::vector<DunImage*> mVectorOfAllImg;
};

