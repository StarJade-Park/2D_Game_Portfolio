#include <..\psklib\Debug.h>
#include <..\psklib\GameFileIO.h>

#include "DunImage.h"
#include "DungreedCore.h"

GameColor DunImage::PosToColor(GamePos _pos)
{
	if ( _pos.XToInt( ) < 0 )
	{
		return 0;
	}

	if ( _pos.YToInt( ) < 0 )
	{
		return 0;
	}

	if ( _pos.XToInt( ) >= mSize.XToInt( ) )
	{
		return 0;
	}

	if ( _pos.YToInt( ) >= mSize.YToInt( ) )
	{
		return 0;
	}

	return GameColor(GetPixel(mhImage, _pos.XToInt( ), _pos.YToInt( )));
}

bool DunImage::Load(const wchar_t* _path)
{
	// �� ���α׷��� �̹��� ���
	mhBitMap = (HBITMAP)LoadImageW(nullptr, _path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if ( NULL == mhBitMap )
	{
		CRASH_PROG;
		return false;
	}

	// NULL -> ���� ȭ��� ȣȯ�Ǵ� DC �޸� ������ش�.
	mhImage = CreateCompatibleDC(NULL);
	if ( NULL == mhImage )
	{
		CRASH_PROG;
		return false;
	}

	mhOldBitMap = (HBITMAP)SelectObject(mhImage, mhBitMap);
	CalcSize(_path);

	return true;
}

void DunImage::CalcSize(const wchar_t* _path)
{
	GameFileRBStream read = GameFileRBStream(_path);

	if ( false == read.IsOpen( ) )
	{
		CRASH_PROG;
		return;
	}

	read >> mBitFileHeader;
	read >> mBitMapInfo;

	mSize.mX = (float)mBitMapInfo.biWidth;
	mSize.mY = (float)mBitMapInfo.biHeight;
}

bool DunImage::Create(GameSize _size)
{
	mhImage = CreateCompatibleDC(nullptr);
	mhBitMap = CreateCompatibleBitmap(
		DungreedCore::MainWindow( ).GetHDC( ),
		_size.XToInt( ),
		_size.YToInt( )
	);

	if ( nullptr == mhImage || nullptr == mhBitMap )
	{
		CRASH_PROG;
		return false;
	}

	mhOldBitMap = (HBITMAP)SelectObject(mhImage, mhBitMap);

	if ( nullptr == mhImage )
	{
		CRASH_PROG;
		return false;
	}

	mSize = _size;

	return true;
}

DunImage::DunImage( )
	: mhImage(nullptr)
	, mSize({ 0.0f, 0.0f })
	, mhBitMap(nullptr)
	, mhOldBitMap(nullptr)
	, mBitFileHeader( )
	, mBitMapInfo( )
{
}

DunImage::~DunImage( )
{
	// ���� ������ ���� ���� ����
	DeleteObject(mhOldBitMap);
	DeleteDC(mhImage);
}
