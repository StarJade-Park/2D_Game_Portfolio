#include "RoomDataMap.h"

RoomData* RoomDataMap::mCurMapStart = nullptr;
std::vector<RoomDoorData> RoomDataMap::mVectorOfOpenData = std::vector<RoomDoorData>( );
std::vector<std::list<RoomDoorData>> RoomDataMap::mVectorOfListOpenData = std::vector<std::list<RoomDoorData>>( );
std::map<int, std::list<RoomDoorData>> RoomDataMap::mMapOfListOpenData = std::map<int, std::list<RoomDoorData>>( );
std::map<__int64, RoomData*> RoomDataMap::mMapOfCurMap = std::map<__int64, RoomData*>( );
std::vector<DunImage*> RoomDataMap::mVectorOfAllImg = std::vector<DunImage*>( );
