#pragma once
#include "DunRender.h"

class DunImage;
class DunImgRender
	: public DunRender
{
public:
	DunImgRender( );
	~DunImgRender( ) = default;

	void SetImage(const wchar_t* _imgName);
	void Render( ) override;

private:
	DunImage* mImage;
};

