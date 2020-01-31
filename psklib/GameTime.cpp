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
	// ��ǻ�Ͱ� �����ϰ� ���� ����
	QueryPerformanceFrequency (&mCountTime);
	// ���α׷� ���� �� �󸶳� �������� ��ȯ
	QueryPerformanceCounter (&mCurTime);
	QueryPerformanceCounter (&mPrevTime);
}

GameTime::GameTimer GameTime::MainTimer;
