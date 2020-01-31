#pragma once
#include <string>

// static class
class GamePath final
{
public:
	GamePath () = delete;
	~GamePath () = delete;

	static const wchar_t* AbsPath (const wchar_t* _name);
	static std::wstring BaseName (const wchar_t* _absPath);
	//static const wchar_t* DirName (const wchar_t* _name);
	static bool IsExsit (const wchar_t* _name);
	//static bool IsFile (const wchar_t* _name);
	//static bool IsDir (const wchar_t* _name);
	static std::wstring Join (const wchar_t* _path, const wchar_t* _name);
	static std::wstring Join (const wchar_t* _path, std::wstring _name);
	static std::wstring Join (std::wstring _path, const wchar_t* _name);
	static std::wstring Join (std::wstring _path, std::wstring _name);
};

