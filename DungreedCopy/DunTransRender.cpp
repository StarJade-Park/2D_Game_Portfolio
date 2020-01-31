#include "DunTransRender.h"
#include "DunResourceManager.h"
#include "DunRenderManager.h"
#include "DunSprite.h"

DunTransRender::DunTransRender( )
	: mSprite(nullptr)
	, mTransRender(GameColor::Magenta)
	, mIndex(def::__tag::InvalidValue)
{
	EMPTY_STATEMENT;
}

void DunTransRender::SetSprite(const wchar_t* _name, int _index)
{
	mSprite = DunResourceManager::FindSpriteOrNull(_name);
	if ( nullptr == mSprite )
	{
		CRASH_PROG;
		return;
	}

	mIndex = _index;

	if ( false == IsCustomSize( ) )
	{
		ResetSpriteSize( );
	}
}

void DunTransRender::SetSprite(std::wstring _name, int _index)
{
	return SetSprite(_name.c_str( ), _index);
}

void DunTransRender::Render( )
{
	if ( nullptr == mSprite )
	{
		CRASH_PROG;
		return;
	}

	if ( false == IsCustomSize( ) )
	{
		ResetSpriteSize( );
	}

	GamePos renderPos = CalcPivotPos( );

	TransparentBlt(
		DunRenderManager::GetBackDC( ),
		renderPos.ToInt( ).mX,
		renderPos.ToInt( ).mY,
		GetSubRectSize( ).ToInt( ).mX,
		GetSubRectSize( ).ToInt( ).mY,
		mSprite->GetImage( ).GetImgDC( ),
		(*mSprite)[mIndex].GetPos( ).ToInt( ).mX,
		(*mSprite)[mIndex].GetPos( ).ToInt( ).mY,
		(*mSprite)[mIndex].GetSize( ).ToInt( ).mX,
		(*mSprite)[mIndex].GetSize( ).ToInt( ).mY,
		mTransRender.GetColor( )
	);
}

void DunTransRender::RenderDebugInfo( )
{
	Rectangle(
		DunRenderManager::GetBackDC( ),
		CalcPivotPos( ).XToInt( ) - 5,
		CalcPivotPos( ).YToInt( ) - 5,
		CalcPivotPos( ).XToInt( ) + 5,
		CalcPivotPos( ).YToInt( ) + 5
	);
}

void DunTransRender::ResetSpriteSize( )
{
	SetSubRectSize((*mSprite).at(mIndex).GetSize( ));
}
