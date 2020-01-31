#include <..\psklib\Well512Random.h>
#include <..\psklib\Debug.h>

#include "RoomData.h"
#include "DunMonster.h"

RoomData::RoomData( )
	: mDoor( )
	, mOtherRoom{ nullptr, nullptr, nullptr, nullptr }
	, mbCreate(false)
	, mMapKey( )
{
	int monsterMax = (int)Well512Random::Instance( ).GetValue(3);

	for ( int i = 0; i < monsterMax; ++i )
	{
		mAllMonster.push_back(DunActor::CreateActor<DunMonster>(L"Monster", true));
	}

	for ( auto& iter : mAllMonster )
	{
		iter->InsertActorToScene(L"TEST");
	}

	EMPTY_STATEMENT;
}

RoomData* RoomData::NextCreateRoom( )
{
	RoomData* result = nullptr;
	int Arr[4] = { 0, 1, 2, 3 };

	// array shuffling
	unsigned int swap_i = 0;
	for ( size_t i = 0; i < 4; ++i )
	{
		swap_i = Well512Random::Instance( ).GetValue(0, 3);
		int temp = Arr[swap_i];
		Arr[swap_i] = Arr[i];
		Arr[i] = temp;
	}

	// nullptr 아닌 곳에서 선택
	for ( size_t i = 0; i < RoomDoorData::DoorDir::MAX; ++i )
	{
		if ( nullptr == mOtherRoom[Arr[i]] )
		{
			if ( RoomDoorData::DoorDir::MAX - 1 == i )
			{
				CRASH_PROG;
				return nullptr;
			}

			continue;
		}

		result = mOtherRoom[Arr[i]];
		break;
	}

	return result;
}
