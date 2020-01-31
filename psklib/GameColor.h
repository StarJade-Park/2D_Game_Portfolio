#pragma once
#include <Windows.h>

class GameColor
{
#pragma region enums
private:
	enum __tag
	{
		zero = 0,
		max = 255
	};
#pragma endregion

public:
	// - Use RGB mecro
	GameColor (COLORREF _color)
	{
		mColor = _color;
	}

	// - defalt = 255, 255, 255
	GameColor (int _r = __tag::max, int _g = __tag::max, int _b = __tag::max)
	{
		mColor = ((COLORREF)(((BYTE)(_r) | ((WORD)((BYTE)(_g)) << 8)) | (((DWORD)(BYTE)(_b)) << 16)));
	}

	~GameColor () = default;

	int GetRed () const
	{
		return mColor & mBitmaskRed;
	}

	int GetGreen () const
	{
		return (mColor & mBitmaskGreen) >> 8;
	}

	int GetBlue () const
	{
		return (mColor & mBitmaskBlue) >> 16;
	}

	COLORREF GetColor( ) const
	{
		return mColor;
	}

	bool operator==(const GameColor& _other)
	{
		return mColor == _other.mColor;
	}

	bool operator!=(const GameColor& _other)
	{
		return mColor != _other.mColor;
	}

public:
	static GameColor Magenta;
	static GameColor Red;
	static GameColor Green; // = Lime
	static GameColor Lime;
	static GameColor Blue;
	static GameColor White;
	static GameColor Black;
	
#pragma region RTLB
	//static GameColor Cyan;
	// TopColor
	static GameColor Top__;
	// LeftColor
	static GameColor Bottom__;
	// BottomColor
	static GameColor Left__;
	// Right
	static GameColor Right__;
#pragma endregion

private:
	static const int mBitmaskRed;  // 255
	static const int mBitmaskGreen; // 65280
	static const int mBitmaskBlue;  // 16711680

	COLORREF mColor;
};