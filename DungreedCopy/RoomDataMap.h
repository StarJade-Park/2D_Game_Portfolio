#pragma once
#include <vector>
#include <map>
#include <list>

#include "RoomDoorData.h"
#include "RoomData.h"

class DunActor;

/*
******* static class *******
- ���� ������ ȣ���� ��
-- Init (path, img init �Ϸ� ��)
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
	// open data ����
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
	// LTRB ������ ������ �ִ°�.
	static std::vector<RoomDoorData> mVectorOfOpenData;
	static std::vector<std::list<RoomDoorData>> mVectorOfListOpenData;

	// ���� ���� ���� �����͸� ������ ����
	static std::map<int, std::list<RoomDoorData>> mMapOfListOpenData;
	static RoomData* mCurMapStart;
	static std::map<__int64, RoomData*> mMapOfCurMap;

private:
	static std::vector<DunImage*> mVectorOfAllImg;
};

