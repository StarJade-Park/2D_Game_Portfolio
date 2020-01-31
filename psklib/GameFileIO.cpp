#include "GameFileIO.h"
#include "Debug.h"

/**************************** Base ****************************/
GameFileStream::GameFileStream (const char* _fileName, const char* _mode)
	: mFile(nullptr)
{
	//assert_msg ("fail file open", GameIO::IsFileExist (_fileName));
	fopen_s (&mFile, _fileName, _mode);
}

GameFileStream::GameFileStream (const wchar_t* _fileName, const wchar_t* _mode)
	: mFile (nullptr)
{
	//assert_msg ("fail file open", GameIO::IsFileExist (_fileName));
	_wfopen_s (&mFile, _fileName, _mode);
}

GameFileStream::~GameFileStream ()
{
	assert_with_msg ("file nullptr", !(nullptr == mFile));
	fclose (mFile);
}

// open: true, non-open: false
bool GameFileStream::IsOpen ()
{
	return (nullptr != mFile);
}
/**************************** Base ****************************/

/**************************** Read Only ****************************/
// file read only
GameFileRStream::GameFileRStream (const char * _fileName)
	: GameFileStream(_fileName, "r")
{
}

// file read only
GameFileRStream::GameFileRStream (const wchar_t * _fileName)
	: GameFileStream (_fileName, L"r")
{
}

GameFileRStream::~GameFileRStream ()
{
}

// binary file read only
GameFileRBStream::GameFileRBStream (const char * _fileName)
	: GameFileStream (_fileName, "rb")
{
}

// binary file read only
GameFileRBStream::GameFileRBStream (const wchar_t * _fileName)
	: GameFileStream (_fileName, L"rb")
{
}

GameFileRBStream::~GameFileRBStream ()
{
}

/**************************** Read Only ****************************/


/**************************** Write Only ****************************/
// file write only
GameFileWStream::GameFileWStream (const char * _fileName)
	: GameFileStream (_fileName, "w")
{
}

// file write only
GameFileWStream::GameFileWStream (const wchar_t * _fileName)
	: GameFileStream (_fileName, L"w")
{
}

GameFileWStream::~GameFileWStream ()
{
}

// binary file read only
GameFileWBStream::GameFileWBStream (const char * _fileName)
	: GameFileStream (_fileName, "wb")
{
}

// binary file read only
GameFileWBStream::GameFileWBStream (const wchar_t * _fileName)
	: GameFileStream (_fileName, L"wb")
{
}

GameFileWBStream::~GameFileWBStream ()
{
}

/**************************** Write Only ****************************/
