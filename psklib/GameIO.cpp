#include <io.h>
#include <string>

#include "GameIO.h"

bool GameIO::IsExist (const char * _fileName)
{
	return (0 == _access_s (_fileName, 0));
}

bool GameIO::IsExist (const wchar_t* _fileName)
{
	return (0 == _waccess_s (_fileName, 0));
}

bool GameIO::IsExist (std::wstring _fileName)
{
	return IsExist (_fileName.c_str ());
}