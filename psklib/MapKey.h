#pragma once

// unnamed union, struct warning
#pragma warning(disable : 4702)
#pragma warning(disable : 4201)

class MapKey
{
public:
	union
	{
		struct
		{
			int X;
			int Y;
		};
		__int64 Key;
	};
};