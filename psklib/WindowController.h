#pragma once
#include <map>
#include <string>

#include <Windows.h>

#include "Geometry.h"
#include "Debug.h"

class WindowController final
{
	/********** member function **********/
public:
	static void InitWndClass (const HINSTANCE& _inst);

	static bool CreateWndClass (const WNDCLASSEXW& _wcex);
	static WNDCLASSEXW FindWndClass (const wchar_t* _name);

	static LRESULT CALLBACK MainWndProcedure (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static WindowController* CreateNewWindowOrNull (const wchar_t* _className, const wchar_t* _windowName, const wchar_t* _titleName, bool _bIsShow = true);
	static WindowController* CreateNewWindowOrNull (const wchar_t* _windowName, const wchar_t* _titleName, bool _bIsShow = true);
	static WindowController* CreateNewWindowOrNull (const wchar_t* _titleName, bool _bIsShow = true);

	static bool DestroyHWindow (HWND _hWnd);

	static int GetWndCount ();

	static void UpdateAllWnd ();

	void SetWndSize (int _sizeX, int _sizeY);
	GameSize GetWndSize ();
	void SetWndPos (int _posX, int _posY);
	void SetWndPosAndSize (int _posX, int _posY, int _sizeX, int _sizeY);

	void CursorOff( );

	void Show ();
	void Hide ();

	HWND GetHWnd () const
	{
		return mhWnd;
	}

	HDC GetHDC () const
	{
		return mhDC;
	}

	GamePos GetMousePos ();
	GamePos GetMouseDir ();

private:
	bool InitHWnd (const wchar_t* _class, const wchar_t* _title);
	void Update ();

	WindowController ()
		: mhWnd(nullptr)
		, mhDC(nullptr)
		, mStyle(NULL)
		, mHMenu(nullptr)
		, mWndSize ({ 0.0f, 0.0f })
	{
		EMPTY_STATEMENT
	};

	~WindowController () = default;

	/********* member variable *********/
private:
	static HINSTANCE mhMainInst;
	static int mWndCounter;

	// WndClass ���� ��� ����
	static std::map<std::wstring, WNDCLASSEXW> mWndClassMap;
	// WndClass�� ���� ������� Window�� �����ϴ� �������
	static std::map<std::wstring, WindowController*> mWndCtrlMap;

	HWND mhWnd;
	HDC mhDC; // device context handle variable

	DWORD mStyle;
	// �츮�� �޴��� ���� ���� ���̹Ƿ�
	// ���� Handle�� ���ϴ� ������ ���� �뵵�� ����
	HMENU mHMenu;

	GameSize mWndSize;
	GamePos mMousePos;
	GamePos mPrevMousePos;
};

