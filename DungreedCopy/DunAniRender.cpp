#include <..\psklib\GameTime.h>

#include "DunAniRender.h"
#include "DunResourceManager.h"
#include "DunRenderManager.h"

DunAniRender::DunAniRender( )
	: mAnimationMap( )
	, mCurAnimation(nullptr)
	, mTransColor(GameColor::Magenta)
{
	EMPTY_STATEMENT;
}

DunAniRender::~DunAniRender( )
{
	for ( auto& iter : mAnimationMap )
	{
		if ( nullptr != iter.second )
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}

void DunAniRender::RenderDebugInfo( )
{
	Rectangle(
		DunRenderManager::GetBackDC( ),
		GetActorPos( ).ToInt( ).mX - 5,
		GetActorPos( ).ToInt( ).mY - 5,
		GetActorPos( ).ToInt( ).mX + 5,
		GetActorPos( ).ToInt( ).mY + 5
	);

	Rectangle(
		DunRenderManager::GetBackDC( ),
		CalcPivotPos( ).XToInt( ) - 5,
		CalcPivotPos( ).YToInt( ) - 5,
		CalcPivotPos( ).XToInt( ) + 5,
		CalcPivotPos( ).YToInt( ) + 5
	);

	//GamePos renderPos = CalcPivotPos( );

	//Rectangle(
	//	DunRenderManager::GetBackDC( ),
	//	renderPos.ToInt( ).mX,
	//	renderPos.ToInt( ).mY,
	//	renderPos.ToInt( ).mX + GetSubRectSize( ).ToInt( ).mX,
	//	renderPos.ToInt( ).mY + GetSubRectSize( ).ToInt( ).mY
	//);
}

bool DunAniRender::IsSameAnimation(const wchar_t* _animationName)
{
	return mCurAnimation == FindAnimationOrNull(_animationName);
}

void DunAniRender::PlayAnimation(const wchar_t* _animationName)
{
	DunAnimationInfo* changeAniInfo = FindAnimationOrNull(_animationName);

	if ( nullptr == changeAniInfo )
	{
		CRASH_PROG;
		return;
	}

	if ( nullptr != changeAniInfo &&
		mCurAnimation == changeAniInfo &&
		false == mCurAnimation->mbResetAble )
	{
		return;
	}

	mCurAnimation = changeAniInfo;
	mCurAnimation->ResetAnimation( );
}

void DunAniRender::CreateAnimation(
	const wchar_t* _animationName, const wchar_t* _spriteName,
	int _startIndex, int _endIndex,
	bool _loopAble /* = false */, float _playTime /* = 0.1f*/)
{
	CreateAnimation(_animationName, _spriteName, _startIndex, _endIndex, _playTime, _loopAble);
}

void DunAniRender::CreateAnimation(
	const wchar_t* _animationName, const wchar_t* _spriteName,
	int _startIndex, int _endIndex,
	float _playTime /* = 0.1f*/, bool _loopAble /* = false */)
{
	if ( nullptr != FindAnimationOrNull(_animationName) )
	{
		CRASH_PROG;
		return;
	}

	DunSprite* findSprite = DunResourceManager::FindSpriteOrNull(_spriteName);

	if ( nullptr == findSprite )
	{
		CRASH_PROG;
		return;
	}

	DunAnimationInfo* newAniInfo = new DunAnimationInfo( );

	newAniInfo->mSprite = findSprite;
	newAniInfo->mStartIndex = _startIndex;
	newAniInfo->mEndIndex = _endIndex;
	newAniInfo->mPlayTime = _playTime;
	newAniInfo->mbLoopAble = _loopAble;
	newAniInfo->ResetAnimation( );

	mAnimationMap.insert(
		std::map<std::wstring, DunAnimationInfo*>::value_type(
			_animationName,
			newAniInfo
		)
	);
}

void DunAniRender::Render( )
{
	if ( nullptr == mCurAnimation )
	{
		CRASH_PROG;
		return;
	}

	mCurAnimation->mCurTime -= GameTime::DeltaTime( );

	if ( 0 >= mCurAnimation->mCurTime )
	{
		++mCurAnimation->mCurIndex;
		mCurAnimation->mCurTime = mCurAnimation->mPlayTime;

		// 애니메이션 재생 후 처리(반복 여부에 따라 결정)
		if ( mCurAnimation->mCurIndex == mCurAnimation->mEndIndex + 1 )
		{
			if ( true == mCurAnimation->mbLoopAble )
			{
				mCurAnimation->mCurIndex = mCurAnimation->mStartIndex;
			}
			else
			{
				mCurAnimation->mCurIndex = mCurAnimation->mEndIndex;
			}
		}
	}

	if ( false == IsCustomSize( ) )
	{
		SetSubRectSize(
			(*(mCurAnimation->mSprite)). \
			GetSpriteRectByIndex(mCurAnimation->mCurIndex).GetSize( )
		);
	}

	GamePos renderPos = CalcPivotPos( );

	TransparentBlt(
		DunRenderManager::GetBackDC( ),
		renderPos.XToInt( ),
		renderPos.YToInt( ),
		GetSubRectSize( ).XToInt( ),
		GetSubRectSize( ).YToInt( ),
		mCurAnimation->mSprite->GetImage( ).GetImgDC( ),
		(*(mCurAnimation->mSprite)).at(mCurAnimation->mCurIndex).GetPos( ).ToInt( ).mX,
		(*(mCurAnimation->mSprite)).at(mCurAnimation->mCurIndex).GetPos( ).ToInt( ).mY,
		(*(mCurAnimation->mSprite)).at(mCurAnimation->mCurIndex).GetSize( ).ToInt( ).mX,
		(*(mCurAnimation->mSprite)).at(mCurAnimation->mCurIndex).GetSize( ).ToInt( ).mY,
		mTransColor.GetColor( )
	);
}

DunAniRender::DunAnimationInfo* DunAniRender::FindAnimationOrNull(const wchar_t* _animationName)
{
	const auto& findIter = mAnimationMap.find(_animationName);

	if ( mAnimationMap.end( ) == findIter )
	{
		return nullptr;
	}

	return findIter->second;
}
