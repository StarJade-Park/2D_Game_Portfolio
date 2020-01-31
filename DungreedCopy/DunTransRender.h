#pragma once
#include <..\psklib\GameColor.h>

#include "DunRender.h"

class DunSprite;
class DunTransRender
	: public DunRender
{
public:
	DunTransRender( );
	~DunTransRender( ) = default;

	void SetSprite(const wchar_t* _name, int _index = 0);
	void SetSprite(std::wstring _name, int _index = 0);
	DunSprite& GetSprite( )
	{
		return *mSprite;
	}

	void Render( ) override;
	void RenderDebugInfo( ) override;

	void ResetSpriteSize( );

private:
	DunSprite* mSprite;
	GameColor mTransRender; // default = Magenta
	int mIndex;
};

