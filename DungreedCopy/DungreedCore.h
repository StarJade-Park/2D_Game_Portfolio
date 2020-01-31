#pragma once
#include <..\psklib\WindowController.h>

class DungreedCore final
{
	friend int APIENTRY wWinMain (_In_ HINSTANCE hInstance,
								_In_opt_ HINSTANCE hPrevInstance,
								_In_ LPWSTR    lpCmdLine,
								_In_ int       nCmdShow);
public:
	// valueÇü singleton
	static WindowController* mMainWndCtrl;
	// valueÇü singleton
	static WindowController& MainWindow ()
	{
		return *mMainWndCtrl;
	}

	static void StartGame ();
#pragma region init_functions
	static void InitBase( );
	static void InitPath( );
	static void InitImg( );
	static void InitSound( );
	static void InitSprite( );
	static void InitScene( );
	static void InitKeys( );
	static void InitColLinks( );
#pragma endregion
	static MSG RunGame ();
	static void EndGame ();
	static void ConductGame ();

private:
	DungreedCore () = default;
	~DungreedCore () = default;
};

