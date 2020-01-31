#include <Windows.h>

#include "GameDirectory.h"
#include "GameDirectoryInfo.h"
#include "GamePath.h"
#include "GameIO.h"

#include "Debug.h"

std::wstring GameDirectory::mRootPath;
wchar_t GameDirectory::root[def::__tag::StrMaxLength] = { NULL };
std::map<std::wstring, GameDirectoryInfo> GameDirectory::mPathMap;

bool GameDirectory::Init ()
{
	SetRootPath ();
	MoveRootPathToParent ();
	return MoveRootPathTo (L"BIN");
}

std::wstring GameDirectory::GetRootPath ()
{
	return mRootPath;
}

void GameDirectory::SetRootPath (const wchar_t* _rootPath /*= nullptr*/)
{
	if (NULL == root[0] && nullptr == _rootPath)
	{
		GetCurrentDirectoryW (def::__tag::StrMaxLength, root);
		mRootPath = root;
		return;
	}

	mRootPath = _rootPath;
}

void GameDirectory::MoveRootPathToParent ()
{
	size_t cutSize = mRootPath.find_last_of (L'\\', mRootPath.size ());

	mRootPath.replace (cutSize, mRootPath.size (), L"");
}

bool GameDirectory::MoveRootPathTo (const wchar_t* _name)
{
	size_t originSize = mRootPath.size ();
	mRootPath.append (L"\\").append (_name);

	if (false == GameIO::IsExist (mRootPath))
	{
		mRootPath.replace (originSize, mRootPath.size (), L"");
		CRASH_PROG;
		return false;
	}

	return true;
}

bool GameDirectory::InsertPathMap (const wchar_t* _path)
{
	return InsertPathMap (_path, _path);
}

// - _path : root path 기준 상대 경로
bool GameDirectory::InsertPathMap (const wchar_t* _name, const wchar_t* _path)
{
	GameDirectoryInfo newDir = GameDirectoryInfo (GetRootPath ());
	
	if (false == newDir.MoveToByAbsPath (_path))
	{
		CRASH_PROG;
		return false;
	}

	mPathMap.insert (std::map<std::wstring, GameDirectoryInfo>::value_type (_name, newDir));
	
	return true;
}

GameDirectoryInfo GameDirectory::FindPathToDirOrNull (const wchar_t* _name)
{
	std::map<std::wstring, GameDirectoryInfo>::iterator findIter = mPathMap.find (_name);

	if (mPathMap.end () == findIter)
	{
		CRASH_PROG;
		return GameDirectoryInfo ();
	}

	return findIter->second;
}

std::wstring GameDirectory::FindPathToStrOrNull (const wchar_t* _name)
{
	return FindPathToDirOrNull (_name).GetDirAbsPath ();
}