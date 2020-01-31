#pragma once
#include <list>

#include "DunActor.h"

class DunAniRender;
//class GameSoundPlayer;

class SealStone
	: public DunActor
{
public:
	enum _SealDir
	{
		Right, Down, Invalid
	};

public:
	// - enum _SealDir{ Right, Down };
	SealStone( )
	{

	}
	SealStone(const int _stoneCount, float _startPos, const _SealDir _dir, const int _stoneSize = 1);

	~SealStone( ) = default;

	void Sealed( );
	void UnSealed( );

	SealStone& operator=(const SealStone& _other)
	{
		mStartPos = _other.mStartPos;
		mListOfStone = _other.mListOfStone;
		mDir = _other.mDir;
		return *this;
	}

public:
	float mStartPos;
	std::list<DunAniRender*> mListOfStone;
	_SealDir mDir;
	//GameSoundPlayer* mSealSound;
};

