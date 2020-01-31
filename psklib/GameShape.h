#pragma once
#include "GamePos.h"
#include "PivotDirection.h"

class GameShape
{
public:
	GamePos GetPos( ) const
	{
		return mPos;
	}

	void SetPos(const GamePos& _pos)
	{
		mPos = _pos;
	}

	PivotDirection GetPivot() const
	{
		return mePivot;
	}

	void SetPivot(const PivotDirection _ePivot)
	{
		mePivot = _ePivot;
	}

protected:
	GameShape( )
		: mPos({ 0.0f, 0.0f })
		, mePivot(PivotDirection::LeftTop)
	{
		EMPTY_STATEMENT;
	}

	GameShape(const GamePos& _pos)
		: mPos(_pos)
		, mePivot(PivotDirection::LeftTop)
	{
		EMPTY_STATEMENT;
	}

	GameShape(PivotDirection _ePivot)
		: mPos({ 0.0f, 0.0f })
		, mePivot(_ePivot)
	{
		EMPTY_STATEMENT;
	}

	GameShape(const GamePos& _pos, PivotDirection _ePivot = PivotDirection::LeftTop)
		: mPos(_pos)
		, mePivot(_ePivot)
	{
		EMPTY_STATEMENT;
	}

	virtual ~GameShape( ) = default;

protected:
	GamePos mPos;
	PivotDirection mePivot;
};

