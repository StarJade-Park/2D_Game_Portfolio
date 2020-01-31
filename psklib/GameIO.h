#pragma once
#include <string>

// - Static class for exist file/directory
class GameIO
{
public:
	GameIO () = delete;
	~GameIO () = delete;

public:
	// - Folder(Directory), File ���� Ȯ��
	// - true : ����, false : ����
	static bool IsExist (const char* _fileName);

	// - Folder(Directory), File ���� Ȯ��
	// - true : ����, false : ����
	static bool IsExist (const wchar_t* _fileName);

	// - Folder(Directory), File ���� Ȯ��
	// - true : ����, false : ����
	static bool IsExist (std::wstring _fileName);
};

