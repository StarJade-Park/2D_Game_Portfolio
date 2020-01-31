#include <..\psklib\GameColor.h>
#include <..\psklib\Well512Random.h>
#include <..\psklib\Debug.h>

#include "RoomDataMap.h"

void RoomDataMap::Init( )
{
	mVectorOfListOpenData.reserve(RoomDoorData::DoorDir::MAX);
	for ( size_t i = 0; i < RoomDoorData::DoorDir::MAX; ++i )
	{
		mVectorOfListOpenData.push_back(std::list<RoomDoorData>( ));
	}

	DataImgLoad( );
}

void RoomDataMap::ClearCurMap( )
{
	if ( 0 >= mMapOfCurMap.size( ) )
	{
		return;
	}

	for ( auto& iter : mMapOfCurMap )
	{
		if ( nullptr != iter.second )
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	mMapOfCurMap.clear( );
}

RoomDoorData RoomDataMap::FindOpenRoom(RoomDoorData::DoorDir _dir, int _Count)
{
	std::vector<RoomDoorData> randData = std::vector<RoomDoorData>( );
	randData.reserve(50);
	for ( auto& iter : mVectorOfListOpenData[_dir] )
	{
		if ( _Count <= iter.mOpenCount )
		{
			randData.push_back(iter);
		}
	}

	return randData.at(Well512Random::Instance( ).GetValue((unsigned int)randData.size( )));
}

RoomData* RoomDataMap::CreateRandomDun(int _count /*= 2*/)
{
	// 기존맵이 있다면 다 지운다. 
	ClearCurMap( );

	RoomData* pStart = new RoomData( );
	--_count;

	pStart->mMapKey = { 0, 0 };
	mMapOfCurMap.insert(std::map<__int64, RoomData*>::value_type(pStart->mMapKey.Key, pStart));

	// 디폴트 복사 생성이 일어날 것이다.
	pStart->mDoor = \
		mVectorOfOpenData[Well512Random::Instance( ).GetValue((unsigned int)mVectorOfOpenData.size( ))];
	
	RoomData* pCur = pStart;
	while ( 0 != _count )
	{
		for ( size_t dir_index = 0; dir_index < RoomDoorData::DoorDir::MAX; ++dir_index)
		{
			if ( true == pCur->mDoor.mbOpenArr[dir_index] )
			{
				// 해당 위치에 이미 생성된 방이 있는지 확인
				MapKey NextIndex = pCur->mMapKey;

				switch ( dir_index )
				{
				case RoomDoorData::DoorDir::Left:
					NextIndex.X = pCur->mMapKey.X - 1;
					NextIndex.Y = pCur->mMapKey.Y;
					break;
				case RoomDoorData::DoorDir::Right:
					NextIndex.X = pCur->mMapKey.X + 1;
					NextIndex.Y = pCur->mMapKey.Y;
					break;
				case RoomDoorData::DoorDir::Top:
					NextIndex.X = pCur->mMapKey.X;
					NextIndex.Y = pCur->mMapKey.Y - 1;
					break;
				case RoomDoorData::DoorDir::Bottom:
					NextIndex.X = pCur->mMapKey.X;
					NextIndex.Y = pCur->mMapKey.Y + 1;
					break;
				default:
					CRASH_PROG;
					break;
				}

				if ( mMapOfCurMap.end( ) != mMapOfCurMap.find(NextIndex.Key) )
				{
					continue; // 이미 있으므로 생성하지 않음
				}

				RoomData* NewRoom = new RoomData( );
				--_count;

				switch ( dir_index )
				{
				case RoomDoorData::DoorDir::Left:
					NewRoom->mOtherRoom[RoomDoorData::DoorDir::Right] = pCur;
					NewRoom->mDoor = FindOpenRoom(RoomDoorData::DoorDir::Right, 2);
					break;
				case RoomDoorData::DoorDir::Right:
					NewRoom->mOtherRoom[RoomDoorData::DoorDir::Left] = pCur;
					NewRoom->mDoor = FindOpenRoom(RoomDoorData::DoorDir::Left, 2);
					break;
				case RoomDoorData::DoorDir::Top:
					NewRoom->mOtherRoom[RoomDoorData::DoorDir::Bottom] = pCur;
					NewRoom->mDoor = FindOpenRoom(RoomDoorData::DoorDir::Bottom, 2);
					break;
				case RoomDoorData::DoorDir::Bottom:
					NewRoom->mOtherRoom[RoomDoorData::DoorDir::Top] = pCur;
					NewRoom->mDoor = FindOpenRoom(RoomDoorData::DoorDir::Top, 2);
					break;
				default:
					CRASH_PROG;
					break;
				}

				NewRoom->mMapKey = NextIndex;
				
				pCur->mOtherRoom[dir_index] = NewRoom;

				mMapOfCurMap.insert(
					std::map<__int64, RoomData*>::value_type(
						NewRoom->mMapKey.Key, NewRoom/*pCur->mOtherRoom[dir_index]*/
					)
				);

				if ( 0 >= _count )
				{
					CloseNullDoor();
					mCurMapStart = pStart;
					return mCurMapStart;
				}
			} // if ( true == pCur->mDoor.mbOpenArr[dir_index] )
		} // for ( size_t dir_index = 0; dir_index < RoomDoorData::DoorDir::MAX; ++dir_index)
		pCur->mbCreate = true;
		pCur = pCur->NextCreateRoom( );
		if ( nullptr == pCur )
		{
			CRASH_PROG;
		}
	} // while ( 0 != _count )

	CloseNullDoor();
	mCurMapStart = pStart;
	return mCurMapStart;
}

void RoomDataMap::CloseNullDoor()
{
	for ( auto& iter : mMapOfCurMap )
	{
		for ( size_t index = 0; index < RoomDoorData::DoorDir::MAX; ++index )
		{
			if ( true == iter.second->mDoor.mbOpenArr[index] && \
				nullptr == iter.second->mOtherRoom[index] )
			{
				RoomDoorData tempData = iter.second->mDoor;
				tempData.mbOpenArr[index] = false;

				const auto& changeRoomIter = mMapOfListOpenData.find(tempData.GetKey( ));
				if ( mMapOfListOpenData.end( ) == changeRoomIter )
				{
					CRASH_PROG;
					return;
				}

				std::vector<RoomDoorData> VectorOfRandData = { changeRoomIter->second.begin( ), changeRoomIter->second.end( ) };
				
				RoomDoorData& randData = \
					VectorOfRandData.at(Well512Random::Instance( ).\
								GetValue((unsigned int)VectorOfRandData.size( )));
				iter.second->mDoor = randData;
			}
		}
	}
}
