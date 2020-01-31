#pragma once
#include <unordered_map>
#include <string>

class DunImage;
class DunSprite;
class DunResourceManager
{
	friend class KeyDestroyer;
public:
	static DunImage* FindImageOrNull(const wchar_t* _name);
	static DunImage* LoadImageOrNull(const wchar_t* _path);
	static DunImage* LoadImageOrNull(const wchar_t* _name, const wchar_t* _path);

	static DunSprite* FindSpriteOrNull(const wchar_t* _name);
	static DunSprite* CreateSprite(const wchar_t* _imageName, int _x, int _y);
	static DunSprite* CreateSprite(const wchar_t* _imageName, const wchar_t* _spriteName, int _x, int _y);

private:
	DunResourceManager( ) = default;
	~DunResourceManager( ) = default;

#pragma region ResDestroyer
	class ResDestroyer
	{
	public:
		~ResDestroyer( )
		{
			DunResourceManager::DestructRes( );
		}
	};
	static ResDestroyer mResDestructor;

	static void DestructRes( );
#pragma endregion

private:
	static std::unordered_map<std::wstring, DunImage*> mImgMap;
	static std::unordered_map<std::wstring, DunSprite*> mSpriteMap;
};

