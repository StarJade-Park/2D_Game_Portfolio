#include <Windows.h>
#include <stdlib.h>

#include "GameIO.h"
#include "GamePath.h"
#include "GameDirectory.h"

const wchar_t* GamePath::AbsPath (const wchar_t* _name)
{
	std::wstring absPath = GameDirectory::GetRootPath ();
	return _wfullpath (
		nullptr, absPath.append (L"\\").append (_name).c_str (), def::__tag::StrMaxLength
	);
}

std::wstring GamePath::BaseName (const wchar_t* _absPath)
{
	std::wstring path = std::wstring (_absPath);

	size_t cutSize = path.find_last_of (L'\\', path.size ());

	return path.replace (0, cutSize + 1, L"");
}

bool GamePath::IsExsit (const wchar_t* _name)
{
	return GameIO::IsExist(_name);
}

std::wstring GamePath::Join (const wchar_t* _path, const wchar_t* _name)
{
	return std::wstring (_path).append (L"\\").append (_name);
}

std::wstring GamePath::Join (const wchar_t* _path, std::wstring _name)
{
	return std::wstring (_path).append (L"\\").append (_name);
}

std::wstring GamePath::Join (std::wstring _path, const wchar_t* _name)
{
	return _path.append (L"\\").append (_name);
}

std::wstring GamePath::Join (std::wstring _path, std::wstring _name)
{
	return _path.append (L"\\").append (_name);
}
