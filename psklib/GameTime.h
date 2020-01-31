#pragma once
#include <Windows.h>

class GameTime final
{
public:
#pragma region gametimer_class
	class GameTimer
	{
		friend GameTime;
	public:
		float Update ();
		void Reset ();

	private:
		GameTimer ();
		~GameTimer () = default;

	private:
		LARGE_INTEGER mCountTime;
		LARGE_INTEGER mCurTime;
		LARGE_INTEGER mPrevTime;
		double mdDeltaTime;
		float mfDeltaTime;
	};
#pragma endregion

public:
	static float DeltaTime ()
	{
		return MainTimer.mfDeltaTime;
	}

	static void Update( )
	{
		MainTimer.Update( );
	}

	static void Reset( )
	{
		MainTimer.Reset( );
	}

private:
	GameTime () = default;
	~GameTime () = default;

private:
	static GameTimer MainTimer;
};
