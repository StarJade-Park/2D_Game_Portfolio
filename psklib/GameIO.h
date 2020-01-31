#pragma once
#include <string>

// - Static class for exist file/directory
class GameIO
{
public:
	GameIO () = delete;
	~GameIO () = delete;

public:
	// - Folder(Directory), File 존재 확인
	// - true : 있음, false : 없음
	static bool IsExist (const char* _fileName);

	// - Folder(Directory), File 존재 확인
	// - true : 있음, false : 없음
	static bool IsExist (const wchar_t* _fileName);

	// - Folder(Directory), File 존재 확인
	// - true : 있음, false : 없음
	static bool IsExist (std::wstring _fileName);
};

