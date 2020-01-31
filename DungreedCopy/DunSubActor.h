#pragma once
#include <..\psklib\Geometry.h>
#include <..\psklib\PivotDirection.h>
#include "DunObject.h"

class DunActor;
class DunSubActor
	: public DunObject
{
public:
#pragma region getset
	inline GamePos GetActorPos( );
	void SetActorPos(GamePos _pos);

	DunActor& GetActor( ) const
	{
		return *mActor;
	}

	void OnCameraEffect( )
	{
		mbCameraEffect = true;
	}

	void OffCameraEffect( )
	{
		mbCameraEffect = false;
	}

	// - 출력 크기 지정
	void SetSubRectSize(const GameSize& _renderSize)
	{
		mSubRect.SetSize(_renderSize);
		mbCanSizeCustom = true;
	}

	GameSize GetSubRectSize() const
	{
		return mSubRect.GetSize();
	}

	void SetSubRectPos(const GamePos& _renderPivot)
	{
		mSubRect.SetPos(_renderPivot);
		mePivot = PivotDirection::Custom;
	}

	GamePos GetSubRectPos() const
	{
		return mSubRect.GetPos();
	}

	void SetRenderPosMode(PivotDirection _pivot)
	{
		mePivot = _pivot;
	}

	GamePos CalcPivotPos( );

	PivotDirection GetPivotMode( )
	{
		return mSubRect.GetPivot( );
	}

	void SetSubPivotMode(const PivotDirection _pivotMode)
	{
		mePivot = _pivotMode;
		mSubRect.SetPivot(_pivotMode);
	}

	GamePos GetPivotPos( )
	{
		return mSubRect.GetPos( );
	}

	void SetPivotPos(const GamePos& _pivotPos)
	{
		mSubRect.SetPos(_pivotPos);
		mSubRect.SetPivot(PivotDirection::Custom);
	}

	bool IsCustomSize( )
	{
		return mbCanSizeCustom;
	}
#pragma endregion

	inline bool IsCanUpdate( ) override;
	inline bool IsDied( ) override;

protected:
	DunSubActor( );
	virtual ~DunSubActor( ) = 0;

protected:
	DunActor* mActor;
	bool mbCanSizeCustom;
	bool mbCameraEffect;

	PivotDirection mePivot;
	GameRectangle mSubRect;
};

