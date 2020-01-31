#pragma once
#include <Windows.h>
#include <..\psklib\GameColor.h>
#include <..\psklib\Geometry.h>

#include "DunResource.h"

class DunImage
	: public DunResource
{
	friend class DunResourceManager;
	friend class DunRenderManager;
	friend class DunRoom;
	friend class RoomDataMap;
public:
#pragma region getset
	inline HDC GetImgDC( )
	{
		return mhImage;
	}

	inline GameSize GetSize( )
	{
		return mSize;
	}

	std::wstring& GetName( )
	{
		return mName;
	}

	void SetName(std::wstring _name)
	{
		mName = _name;
	}

	GameColor PosToColor(GamePos _pos);
#pragma endregion

	bool Load(const wchar_t* _path) override;
	void CalcSize(const wchar_t* _path) override;
	bool Create(GameSize _size);

private:
	DunImage( );
	~DunImage( ) override;

private:
	std::wstring mName;
	HDC mhImage;
	GameSize mSize;
	HBITMAP mhBitMap;
	HBITMAP mhOldBitMap;
	BITMAPFILEHEADER mBitFileHeader;
	BITMAPINFOHEADER mBitMapInfo;
};

