#pragma once
#include <string>
#include <map>
#include <list>

#include <..\psklib\tags.h>

class DunCollider;
class DunCollisionManager
{
	friend DunCollider;
public:
#pragma region singleton
	static DunCollisionManager& Instance( )
	{
		static DunCollisionManager collMgr;
		return collMgr;
	}
#pragma endregion

	bool IsLinked(const wchar_t* _Left, const wchar_t* _Right);
	void SetLink(const wchar_t* _Left, const wchar_t* _Right);

	void Release( );
	void Collide( );

	void RenderDebugInfo( );
	void ClearAllCollider( );

private:
	DunCollisionManager( )
		: mMapOfColList( )
		, mMapOfLinkData( )
	{
		EMPTY_STATEMENT;
	}

	~DunCollisionManager( ) = default;

	void CollideGroupToGroup(const wchar_t* _left, const wchar_t* _right);
	void CollideGroupSelf(const wchar_t* _thisName);
	void PushCollider(DunCollider* _col);

private:
	class LinkData
	{
	public:
		LinkData( ) = default;
		~LinkData( ) = default;

	public:
		std::wstring leftName;
		std::wstring rightName;
	};

private:
	std::map<std::wstring, std::list<DunCollider*>> mMapOfColList;
	std::map<std::wstring, LinkData> mMapOfLinkData;
};

