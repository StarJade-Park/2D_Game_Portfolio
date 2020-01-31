#include <Windows.h>

#include "GameIO.h"
#include "GameDirectoryInfo.h"
#include "GameDirectory.h"
#include "GamePath.h"
#include "Debug.h"

GameDirectoryInfo::GameDirectoryInfo ()
	: mFullPath (EMPTY_STATEMENT)
{
}

GameDirectoryInfo::GameDirectoryInfo (const wchar_t* _path)
	: mFullPath (_path)
{
}

GameDirectoryInfo::GameDirectoryInfo (std::wstring _path)
	: mFullPath (_path.c_str ())
{
}

GameDirectoryInfo::GameDirectoryInfo (const GameDirectoryInfo& _other)
	: mFullPath (_other.mFullPath)
{
}

GameDirectoryInfo::~GameDirectoryInfo ()
{
}

std::wstring GameDirectoryInfo::GetDirName () const
{
	return GamePath::BaseName (mFullPath.c_str ());
}

const wchar_t* GameDirectoryInfo::GetDirAbsPath () const
{
	return mFullPath.c_str ();
}

size_t GameDirectoryInfo::GetDirLength () const
{
	return mFullPath.size ();
}

void GameDirectoryInfo::MoveToParent ()
{
	size_t cutSize = mFullPath.find_last_of (L'\\', mFullPath.size ());
	if (0 >= cutSize)
	{
		CRASH_PROG;
	}

	mFullPath.replace (cutSize, mFullPath.size (), L"");
}

bool GameDirectoryInfo::MoveToChild (const wchar_t* _name)
{
	size_t originSize = mFullPath.size ();
	mFullPath.append (L"\\").append (_name);

	if (false == GameIO::IsExist (mFullPath))
	{
		CRASH_PROG;
		mFullPath.replace (originSize, mFullPath.size (), L"");
		return false;
	}

	return true;
}

bool GameDirectoryInfo::MoveToByAbsPath (const wchar_t* _name)
{
	std::wstring prevPath = mFullPath;
	mFullPath.clear ();
	mFullPath.append (_name);

	if (false == GameIO::IsExist (mFullPath))
	{
		CRASH_PROG;
		mFullPath = prevPath;
		return false;
	}

	return true;
}

bool GameDirectoryInfo::IsExsit (const wchar_t* _name) const
{
	return GamePath::IsExsit (GamePath::Join (mFullPath, _name).c_str ());
}

std::vector<std::wstring> GameDirectoryInfo::GetAllFilesToStr ()
{
	std::vector<std::wstring> files;
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if (INVALID_HANDLE_VALUE ==
		(dir = FindFirstFileW ((mFullPath + L"\\*").c_str (), &file_data))
		)
	{
		files.reserve (0);
		return files; /* No files found */
	}
	else
	{
		files.reserve (50);
	}

	do {
		const std::wstring file_name = file_data.cFileName;
		const std::wstring full_file_name = mFullPath + L"\\" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (L'.' == file_name[0])
		{
			continue;
		}

		if (true == is_directory)
		{
			continue;
		}

		files.push_back (full_file_name);
	} while (TRUE == FindNextFileW (dir, &file_data));

	FindClose (dir);

	return files;
}
