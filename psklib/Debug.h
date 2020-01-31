#pragma once

#include <string>
#include <Windows.h>
#include <assert.h>
#include <crtdbg.h>

#define EMPTY_STATEMENT
#define CRASH_PROG assert(false)
#define assert_with_msg(expr, msg) assert(expr && msg)
#define assert_msg(msg) assert(msg && false)

#ifdef _DEBUG
// - Static class for check memory leak
class MemLeakCheker final
{
public:
	MemLeakCheker () = delete;
	~MemLeakCheker () = delete;

	// 메모리의 누수를 확인할 수 있습니다.
	// _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
	static void SetLeakCheckFlag ()
	{
		_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	// - Leak line 찾는 함수
	static void CheckLeakByLine(long _leakLineNumber)
	{
		_CrtSetBreakAlloc(_leakLineNumber);
	}
};

class DebugFlag final
{
public:
	static DebugFlag& Instance( )
	{
		static DebugFlag debug;
		return debug;
	}

	void SetOnFlag( )
	{
		mbFlagOfDebug = true;
	}

	void SetOffFlag( )
	{
		mbFlagOfDebug = false;
	}

	bool IsFlagSet( )
	{
		return mbFlagOfDebug;
	}

private:
	DebugFlag( )
		: mbFlagOfDebug(false)
	{
		EMPTY_STATEMENT;
	}

	~DebugFlag( ) = default;

private:
	bool mbFlagOfDebug;
};
#endif // _DEBUG