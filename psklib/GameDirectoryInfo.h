#pragma once
#include <vector>
#include <string>

class GameDirectoryInfo
{
public:
	// - path = nullptr
	GameDirectoryInfo ();

	GameDirectoryInfo (const wchar_t* _path);
	GameDirectoryInfo (std::wstring _path);
	GameDirectoryInfo (const GameDirectoryInfo& _other);
	~GameDirectoryInfo ();

	std::wstring GetDirName () const;
	const wchar_t* GetDirAbsPath () const;
	size_t GetDirLength () const;

	void MoveToParent ();
	bool MoveToChild (const wchar_t* _name);
	bool MoveToByAbsPath (const wchar_t* _name);

	bool IsExsit (const wchar_t* _name) const;

	// https://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c
	// - WinApi �Լ��� ���� ����Ͽ���
	// - FAIL = vector size�� 0
	// - SUCCESS = vector size�� 0�� �ƴ�
	std::vector<std::wstring> GetAllFilesToStr();

private:
	std::wstring mFullPath;
};

