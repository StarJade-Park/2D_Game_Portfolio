#pragma once
#include <..\psklib\GameColor.h>

#include "DunRender.h"
#include "DunSprite.h"

class DunAniRender
	: public DunRender
{
private:
#pragma region aniinfo_class
	class DunAnimationInfo
	{
	public:
		DunAnimationInfo( )
			: mSprite(nullptr)
			, mbResetAble(false), mbLoopAble(false)
			, mCurIndex(0), mStartIndex(0), mEndIndex(-999)
			, mCurTime(-999.0f), mPlayTime(0.1f)
		{
			EMPTY_STATEMENT;
		}

		~DunAnimationInfo( ) = default;

		void ResetAnimation( )
		{
			mCurIndex = mStartIndex;
			mCurTime = mPlayTime;
		}

	public:
		DunSprite* mSprite;
		bool mbResetAble;
		bool mbLoopAble;
		int mStartIndex;
		int mEndIndex;
		int mCurIndex;
		float mPlayTime;
		float mCurTime;
	};
#pragma endregion

public:
	DunAniRender( );
	~DunAniRender( );

	void RenderDebugInfo( ) override;

	bool IsSameAnimation(const wchar_t* _animationName);
	void PlayAnimation(const wchar_t* _animationName);
	void CreateAnimation(
		const wchar_t* _animationName, const wchar_t* _spriteName,
		int _startIndex, int _endIndex,
		bool _loopAble = false, float _playTime = 0.1f
	);
	void CreateAnimation(
		const wchar_t* _animationName, const wchar_t* _spriteName,
		int _startIndex, int _endIndex,
		float _playTime = 0.1f,
		bool _loopAble = false
	);

	void Render( ) override;

private:
	DunAnimationInfo* FindAnimationOrNull(const wchar_t* _animationName);

private:
	std::map<std::wstring, DunAnimationInfo*> mAnimationMap;
	DunAnimationInfo* mCurAnimation;
	GameColor mTransColor;
};

