// DungreedCopy.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//
#include <..\psklib\Debug.h>

#include "DungreedCore.h"
#include "main.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	// warning 비활성화
	hPrevInstance;
	lpCmdLine;
	nCmdShow;
#ifdef _DEBUG
	MemLeakCheker::SetLeakCheckFlag ();
	//MemLeakCheker::CheckLeakByLine(4431);
#endif // _DEBUG

	WindowController::InitWndClass (hInstance);

	DungreedCore::StartGame ();
	MSG msg = DungreedCore::RunGame ();
	DungreedCore::EndGame ();

    return (int) msg.wParam;
}
