#pragma once
#include <string>
#include <map>

#include "tags.h"

// static class
class GameDirectoryInfo;
class GameDirectory final
{
public:
	GameDirectory () = delete;
	~GameDirectory () = delete;

	static bool Init ();

	static std::wstring GetRootPath ();
	static void SetRootPath (const wchar_t* _rootPath = nullptr);

	static void MoveRootPathToParent ();
	static bool MoveRootPathTo (const wchar_t* _name);

	static bool InsertPathMap (const wchar_t* _path);
	static bool InsertPathMap (const wchar_t* _name, const wchar_t* _path);

	static GameDirectoryInfo FindPathToDirOrNull (const wchar_t* _name);
	static std::wstring FindPathToStrOrNull (const wchar_t* _name);

private:
	static std::wstring mRootPath;
	static wchar_t root[def::__tag::StrMaxLength];

	static std::map<std::wstring, GameDirectoryInfo> mPathMap;
};

