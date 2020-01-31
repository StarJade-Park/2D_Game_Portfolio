#include <..\psklib\GamePath.h>
#include<..\psklib\Debug.h>

#include "DunResourceManager.h"
#include "DunImage.h"
#include "DunSprite.h"

std::unordered_map<std::wstring, DunImage*> DunResourceManager::mImgMap;
std::unordered_map<std::wstring, DunSprite*> DunResourceManager::mSpriteMap;
DunResourceManager::ResDestroyer DunResourceManager::mResDestructor; // 선언 순서에 유의


DunImage* DunResourceManager::FindImageOrNull(const wchar_t * _name)
{
	const auto& findIter = mImgMap.find(_name);

	if ( mImgMap.end( ) == findIter )
	{
		return nullptr;
	}

	return findIter->second;
}

DunImage* DunResourceManager::LoadImageOrNull(const wchar_t* _path)
{
	std::wstring key = GamePath::BaseName(_path);
	return LoadImageOrNull(key.c_str( ), _path);
}

DunImage* DunResourceManager::LoadImageOrNull(const wchar_t * _name, const wchar_t * _path)
{
	DunImage* newImage = FindImageOrNull(_name);

	if ( nullptr != newImage )
	{
		CRASH_PROG;
		return nullptr;
	}

	newImage = new DunImage( );

	if ( false == newImage->Load(_path) )
	{
		CRASH_PROG;
		delete newImage;
		newImage = nullptr;
		return nullptr;
	}

	newImage->SetName(_name);
	mImgMap.insert(
		std::unordered_map<std::wstring, DunImage*>::value_type(_name, newImage)
	);

	return newImage;
}

DunSprite* DunResourceManager::FindSpriteOrNull(const wchar_t * _name)
{
	const auto& findIter = mSpriteMap.find(_name);

	if ( mSpriteMap.end( ) == findIter )
	{
		return nullptr;
	}

	return findIter->second;
}

DunSprite* DunResourceManager::CreateSprite(const wchar_t* _imageName, int _x, int _y)
{
	return CreateSprite(_imageName, _imageName, _x, _y);
}

DunSprite* DunResourceManager::CreateSprite(const wchar_t* _imageName, const wchar_t* _spriteName, int _x, int _y)
{
	DunImage* findImg = FindImageOrNull(_imageName);

	if ( nullptr == findImg )
	{
		CRASH_PROG;
	}

	DunSprite* findSprite = FindSpriteOrNull(_spriteName);

	if ( nullptr != findSprite )
	{
		CRASH_PROG;
	}

	findSprite = new DunSprite(findImg);

	findSprite->CutImage(_x, _y);

	mSpriteMap.insert(
		std::unordered_map<std::wstring, DunSprite*>::value_type(_spriteName, findSprite)
	);

	return findSprite;
}

void DunResourceManager::DestructRes( )
{
	for ( auto& iter : mImgMap )
	{
		if ( nullptr == iter.second )
		{
			continue;
		}

		delete iter.second;
		iter.second = nullptr;
	}

	for ( auto& iter : mSpriteMap )
	{
		if ( nullptr == iter.second )
		{
			continue;
		}

		delete iter.second;
		iter.second = nullptr;
	}
}
