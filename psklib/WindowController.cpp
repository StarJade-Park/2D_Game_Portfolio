#include "Debug.h"
#include "WindowController.h"


HINSTANCE WindowController::mhMainInst;
int WindowController::mWndCounter = 0;

std::map<std::wstring, WNDCLASSEXW> WindowController::mWndClassMap;
std::map<std::wstring, WindowController*> WindowController::mWndCtrlMap;

// HINSTANCE를 받아 WNDCLASSEXW를 초기화하고 등록합니다.
void WindowController::InitWndClass (const HINSTANCE& _inst)
{
	mhMainInst = _inst;

	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof (WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWndProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _inst;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor (nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Default";
	wcex.hIconSm = NULL;

	CreateWndClass (wcex);
}

bool WindowController::CreateWndClass (const WNDCLASSEXW& _wcex)
{
	// RegisterClassExW가 실패하면 0을 반환
	if (0 == RegisterClassExW (&_wcex))
	{
		assert_msg ("Fail class regist");
		return false;
	}

	mWndClassMap.insert (
		std::map<std::wstring, WNDCLASSEXW>::value_type (_wcex.lpszClassName, _wcex)
	);

	return true;
}

WNDCLASSEXW WindowController::FindWndClass (const wchar_t* _name)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator findIter = mWndClassMap.find (_name);

	if (mWndClassMap.end () == findIter)
	{
		WNDCLASSEXW W;
		W.hInstance = 0;
		return W;
	}
	return findIter->second;
}

// 창의 메시지를 처리합니다.
LRESULT WindowController::MainWndProcedure (HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		/*HDC hdc = */BeginPaint (_hWnd, &ps);
		EndPaint (_hWnd, &ps); // 요청하지 않으면 계속해서 그리기 위한 메시지 전달
		break;
	}
	case WM_DESTROY:
		//PostQuitMessage (0);
		DestroyHWindow (_hWnd);
		break;
	default:
		return DefWindowProc (_hWnd, _message, _wParam, _lParam);
	}

	return 0;
}

// 창의 class, window, title 이름을 정하여 생성합니다.
// _bIsShow의 default는 true입니다.
WindowController* WindowController::CreateNewWindowOrNull (const wchar_t* _className, const wchar_t* _windowName, const wchar_t* _titleName, bool _bIsShow /*= true*/)
{
	// 생성하고자 하는 창이 이미 있는가
	if (mWndCtrlMap.end () != mWndCtrlMap.find (_className))
	{
		assert_msg("already created window");
		return nullptr;
	}
	WindowController* newWnd = new WindowController ();

	if (false == newWnd->InitHWnd (_className, _titleName))
	{
		assert_msg("fail InitHWnd");
		delete newWnd; // 실패시 지우고 nullptr 반환
		return nullptr;
	}

	mWndCtrlMap.insert (
		std::map<std::wstring, WindowController*>::value_type (_windowName, newWnd)
	);

	if (true == _bIsShow)
	{
		newWnd->Show ();
	}
	else
	{
		newWnd->Hide ();
	}

	++mWndCounter;
	
	return newWnd;
}

// 용도 : 창의 window, title 이름을 정하여 생성합니다.
// _bIsShow의 default는 true입니다.
// class의 이름은 Deault가 됩니다.
WindowController* WindowController::CreateNewWindowOrNull (const wchar_t* _windowName, const wchar_t* _titleName, bool _bIsShow /*= true*/)
{
	return CreateNewWindowOrNull (L"Default", _windowName, _titleName, _bIsShow);
}

// 창의 title 이름을 정하여 생성합니다.
// _bIsShow의 default는 true입니다.
// class, window의 이름은 Deault가 됩니다.
WindowController* WindowController::CreateNewWindowOrNull (const wchar_t* _titleName, bool _bIsShow /*= true*/)
{
	return CreateNewWindowOrNull (L"Default", L"Default", _titleName, _bIsShow);
}

bool WindowController::DestroyHWindow (HWND _hWnd)
{
	std::map<std::wstring, WindowController*>::iterator Loop = mWndCtrlMap.begin ();
	std::map<std::wstring, WindowController*>::iterator End = mWndCtrlMap.end ();

	for (; Loop != End; ++Loop)
	{
		if (Loop->second->mhWnd == _hWnd)
		{
			if (nullptr != Loop->second)
			{
				delete Loop->second;
				Loop->second = nullptr;
			}
			mWndCtrlMap.erase (Loop);
			--mWndCounter;
			return true;
		}
	}

	return true;
}

int WindowController::GetWndCount ()
{
	return mWndCounter;
}

void WindowController::UpdateAllWnd ()
{
	for (auto& iter : mWndCtrlMap)
	{
		iter.second->Update ();
	}
}

void WindowController::SetWndSize (int _sizeX, int _sizeY)
{
	mWndSize.mX = (float)_sizeX;
	mWndSize.mY = (float)_sizeY;

	RECT rc = { 0, 0, _sizeX, _sizeY };
	AdjustWindowRect (&rc, mStyle, false);

	SetWindowPos (
		mhWnd, NULL,
		NULL, NULL,
		rc.right - rc.left, rc.bottom - rc.top,
		SWP_NOMOVE | SWP_NOZORDER
	);
}

GameSize WindowController::GetWndSize ()
{
	return mWndSize;
}

void WindowController::SetWndPos (int _posX, int _posY)
{
	SetWindowPos (mhWnd, 0, _posX, _posY, NULL, NULL, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowController::SetWndPosAndSize (int _posX, int _posY, int _sizeX, int _sizeY)
{
	SetWndPos (_posX, _posY);
	SetWndSize (_sizeX, _sizeY);
}

void WindowController::CursorOff( )
{
	SetCursor(NULL);
}

void WindowController::Show ()
{
	ShowWindow (mhWnd, SW_SHOW);
	UpdateWindow (mhWnd);
}

void WindowController::Hide ()
{
	ShowWindow (mhWnd, SW_HIDE);
	UpdateWindow (mhWnd);
}

GamePos WindowController::GetMousePos ()
{
	return mMousePos;
}

GamePos WindowController::GetMouseDir ()
{
	return mMousePos - mPrevMousePos;
}

bool WindowController::InitHWnd (const wchar_t* _class, const wchar_t* _title)
{
	WNDCLASSEXW findClass = FindWndClass (_class);

	if (0 == findClass.hInstance)
	{
		assert_msg("hInstance in find class is 0");
	}

	mStyle = WS_OVERLAPPEDWINDOW;
	mHMenu = GetMenu(mhWnd);

	if (nullptr == findClass.lpszMenuName)
	{
		mHMenu = FALSE;
	}

	mhWnd = CreateWindowW (_class, _title, mStyle,
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, mhMainInst, nullptr);

	if (nullptr == mhWnd)
	{
		assert_msg("mhWnd is null");
		return false;
	}

	mhDC = GetDC (mhWnd);

	if (nullptr == mhDC)
	{
		assert_msg ("mhDC is null");
		return false;
	}

	return true;
}

void WindowController::Update ()
{
	CursorOff( );
	mPrevMousePos = mMousePos;

	POINT point;
	GetCursorPos (&point);
	ScreenToClient (mhWnd, &point);

	mMousePos = GamePos ((float)point.x, (float)point.y);
}
