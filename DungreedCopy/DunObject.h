#pragma once
#include <string>
#include <..\psklib\tags.h>

class DunObject
{
public:
#pragma region getset
	const wchar_t* GetNameChPtr( ) const
	{
		return mName.c_str( );
	}

	std::wstring GetName( ) const
	{
		return mName;
	}

	void SetName(const std::wstring& _name)
	{
		mName = _name;
	}

	virtual bool IsCanUpdate( )
	{
		return mbCanUpdate && false == mbIsDied;
	}

	virtual bool IsDied( )
	{
		return mbIsDied;
	}

	void Die( )
	{
		mbIsDied = true;
	}
#pragma endregion

protected:
	DunObject( )
		: mName(L"NULL")
		, mbIsDied(false)
		, mbCanUpdate(true)
		, mIsDebug(false)
	{
		EMPTY_STATEMENT;
	}

	virtual ~DunObject( ) = default;

public:
	bool mIsDebug;

protected:
	std::wstring mName;
	bool mbIsDied;
	bool mbCanUpdate;
};
