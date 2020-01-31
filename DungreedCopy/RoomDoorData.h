#pragma once
#include <..\psklib\GamePos.h>

namespace __key
{
	constexpr auto KEY_NONE = 0x0000;
	constexpr auto KEY_01 = 0x0001;
	constexpr auto KEY_02 = 0x0010;
	constexpr auto KEY_03 = 0x0100;
	constexpr auto KEY_04 = 0x1000;
}

class DunImage;

class RoomDoorData
{
public:
	enum DoorDir
	{
		Top, Right, Bottom, Left, MAX
	};

public:
	RoomDoorData( )
		: mbOpenArr{ false, false, false, false }
		, mTex(nullptr)
		, mOpenCount(0)
		, otherRoomPos{ {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1} }
	{
		EMPTY_STATEMENT;
	}
	~RoomDoorData( ) = default;

	int GetKey( )
	{
		int key = __key::KEY_NONE;
		if ( true == mbOpenArr[DoorDir::Top] )
		{
			key = key | __key::KEY_01;
		}

		if ( true == mbOpenArr[DoorDir::Right] )
		{
			key = key | __key::KEY_02;
		}

		if ( true == mbOpenArr[DoorDir::Bottom] )
		{
			key = key | __key::KEY_03;
		}

		if ( true == mbOpenArr[DoorDir::Left] )
		{
			key = key | __key::KEY_04;
		}

		return key;
	}

public:
	int mOpenCount;
	bool mbOpenArr[DoorDir::MAX];
	DunImage* mTex;
	GamePos otherRoomPos[RoomDoorData::DoorDir::MAX];
};
