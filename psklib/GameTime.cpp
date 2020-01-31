#include "GameTime.h"

GameTime::GameTimer::GameTimer ()
	: mCountTime(LARGE_INTEGER( ))
	, mCurTime(LARGE_INTEGER( ))
	, mPrevTime(LARGE_INTEGER( ))
	, mdDeltaTime(-999.9f)
	, mfDeltaTime(-999.9f)
{
	Reset ();
}

float GameTime::GameTimer::Update ()
{
	QueryPerformanceCounter (&mCurTime);

	// delta time = curtime - prevtime
	mdDeltaTime
		= ((double)mCurTime.QuadPart - (double)mPrevTime.QuadPart) \
		/ (double)(mCountTime.QuadPart);

	mfDeltaTime = (float)mdDeltaTime;
	mPrevTime = mCurTime;

	return mfDeltaTime;
}

void GameTime::GameTimer::Reset ()
{
	// 컴퓨터가 일정하게 세는 숫자
	QueryPerformanceFrequency (&mCountTime);
	// 프로그램 동작 후 얼마나 세었는지 반환
	QueryPerformanceCounter (&mCurTime);
	QueryPerformanceCounter (&mPrevTime);
}

GameTime::GameTimer GameTime::MainTimer;
