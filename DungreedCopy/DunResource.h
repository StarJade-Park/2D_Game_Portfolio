#pragma once
class DunResource
{
public:
	DunResource( ) = default;
	virtual ~DunResource( ) = default;

	virtual bool Load(const wchar_t* _path) = 0;
	virtual void CalcSize(const wchar_t* _path) = 0;
};

