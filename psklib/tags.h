#pragma once

#define FALL_THROUGH
#define EMPTY_STATEMENT

/*
	C++에서 참조는 포인터의 변형에 불과합니다.
	따라서 둘 중 어느 것이 더 좋고 나쁘냐를 따지는 것은 큰 의미가 없습니다.
	다만 포인터의 경우 nullptr을 전달할 수 있는 장점이 있고,
	참조의 경우 const를 붙이면 상수도 넘길 수 있는 장점이 있습니다.
	즉, 함수의 구현에 유리한 방식을 선택하면 됩니다.
*/
namespace def
{
	enum __tag
	{
		width = 800,
		height = 600,

		StrMaxLength = 1024,
		
		InvalidValue = -12345,
		
		Default_Order = -1000,
	};
}