#pragma once
#include <list>
#include <vector>

#include <..\psklib\GameSize.h>

#include "DunActor.h"
#include "RoomDoorData.h"

class DunTransRender;
class DunAniRender;
class GameSoundPlayer;

class DunRoom
	: public DunActor
{
public:
	enum _order
	{
		DecoOrder = - 98,
		ShowOrder = -99,
		ColOrder = -100,
		DoorOrder = -101,
	};

public:
	DunRoom( );
	~DunRoom( );

	DunTransRender& GetRenderForCol( )
	{
		return *mColWallRender;
	}

	DunTransRender& GetRenderForBG( )
	{
		return *mBackGround;
	}

	DunTransRender& GetRenderForColDoor( )
	{
		return *mDoorColRender;
	}

	DunTransRender& GetRenderForCursor( )
	{
		return *mCursor;
	}

	void ChangeColImg( );
	void ChangeShowImg( );

	bool IsCleared( )
	{
		return mbClear;
	}

	void SwitchClear( )
	{
		mbClear = !mbClear;
	}

private:
	void Update( ) override;
	void ChangePlayerPosByDoorDir(RoomDoorData::DoorDir _dir);
	void ChangeRoom(RoomDoorData::DoorDir _dir);

private:
	GameSize mRoomSize; // TypeOfRoomSize�� ���� ����
	bool mbWormPassageAble; // ��� ��� Ȱ��ȭ ����
	bool mbClear; // Ŭ����(���� �� ����) ���� 

	DunTransRender* mDoorColRender;
	DunTransRender* mColWallRender;
	DunTransRender* mBackGround;
	DunTransRender* mBackGroundGray;
	//DunTransRender* mBackDeco;
	DunTransRender* mCursor;

	std::wstring mCommonUseStr;
	GameSoundPlayer* mDoorSealSound;
};

