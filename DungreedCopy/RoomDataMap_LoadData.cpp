#include <..\psklib\GameFileSystem.h>
#include <..\psklib\Debug.h>

#include "RoomDataMap.h"
#include "DunResourceManager.h"
#include "DunImage.h"

void RoomDataMap::DataImgLoad( )
{
	GameDirectoryInfo dir = GameDirectory::FindPathToDirOrNull(L"room_info");
	std::vector<std::wstring> allFiles = dir.GetAllFilesToStr( );

	mVectorOfAllImg.reserve(allFiles.size( ));

	for ( auto& str : allFiles )
	{
		DunImage* newImg = DunResourceManager::LoadImageOrNull(str.c_str( ));
		if ( nullptr == newImg )
		{
			CRASH_PROG;
			return;
		}

		mVectorOfAllImg.push_back(newImg);
	}

	for ( auto& img : mVectorOfAllImg )
	{
		RoomDoorData NewOpen;
		NewOpen.mbOpenArr[RoomDoorData::DoorDir::Left] = false;
		NewOpen.mbOpenArr[RoomDoorData::DoorDir::Top] = false;
		NewOpen.mbOpenArr[RoomDoorData::DoorDir::Right] = false;
		NewOpen.mbOpenArr[RoomDoorData::DoorDir::Bottom] = false;
		NewOpen.mTex = img;

		for ( size_t y = 0, sizeY = (size_t)img->GetSize( ).mY; y < sizeY; ++y )
		{
			for ( size_t x = 0, sizeX = (size_t)img->GetSize( ).mX; x < sizeX; ++x )
			{
				GameColor color = img->PosToColor({ (float)x, (float)y });

				if ( GameColor::Top__ == color )
				{
					if ( true == NewOpen.mbOpenArr[RoomDoorData::DoorDir::Top] )
					{
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Top].mX += 0.5f;
					}
					else
					{
						NewOpen.mbOpenArr[RoomDoorData::DoorDir::Top] = true;
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Top] = { (float)x, (float)y + 0.5f };
					}

					continue;
				}

				if ( GameColor::Bottom__ == color )
				{
					if ( true == NewOpen.mbOpenArr[RoomDoorData::DoorDir::Bottom] )
					{
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Bottom].mX += 0.5f;
					}
					else
					{
						NewOpen.mbOpenArr[RoomDoorData::DoorDir::Bottom] = true;
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Bottom] = { (float)x, (float)y + 0.5f };
					}

					continue;
				}

				if ( GameColor::Left__ == color )
				{
					if ( true == NewOpen.mbOpenArr[RoomDoorData::DoorDir::Left] )
					{
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Left].mY += 0.5f;
					}
					else
					{
						NewOpen.mbOpenArr[RoomDoorData::DoorDir::Left] = true;
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Left] = { (float)x + 0.5f, (float)y };
					}

					continue;
				}

				if ( GameColor::Right__ == color )
				{
					// 이때 pos 위치를 정하고 카운트 될 때마다 0.5씩 더해준다.
					if ( true == NewOpen.mbOpenArr[RoomDoorData::DoorDir::Right] )
					{
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Right].mY += 0.5f;
					}
					else
					{
						NewOpen.mbOpenArr[RoomDoorData::DoorDir::Right] = true;
						NewOpen.otherRoomPos[RoomDoorData::DoorDir::Right] = { (float)x + 0.5f, (float)y };
					}

					continue;
				}
			}
		} // set room info

		// set other room door pos
		for ( GamePos& InfoPos : NewOpen.otherRoomPos )
		{
			InfoPos *= 50.0f;
		}

		// open door count
		for ( bool bOpen : NewOpen.mbOpenArr )
		{
			if ( true == bOpen )
			{
				NewOpen.mOpenCount++;
			}
		}

		auto iter = mMapOfListOpenData.find(NewOpen.GetKey( ));
		if ( mMapOfListOpenData.end( ) == iter )
		{
			mMapOfListOpenData.insert(
				std::map<int, std::list<RoomDoorData>>::value_type(
					NewOpen.GetKey( ),
					std::list<RoomDoorData>( )
				)
			);

			iter = mMapOfListOpenData.find(NewOpen.GetKey( ));
		}
		iter->second.push_back(NewOpen);

		// LRB 가 뚤린 녀석이라면
		for ( size_t index_dir = 0; index_dir < RoomDoorData::DoorDir::MAX; ++index_dir )
		{
			if ( true == NewOpen.mbOpenArr[index_dir] )
			{
				mVectorOfListOpenData[index_dir].push_front(NewOpen);
				mVectorOfOpenData.push_back(NewOpen);
			}
		} // insert to list of LTRB info
	} // for (auto& img : mVectorOfAllImg)
}