#pragma once

#define FALL_THROUGH
#define EMPTY_STATEMENT

/*
	C++���� ������ �������� ������ �Ұ��մϴ�.
	���� �� �� ��� ���� �� ���� ���ڳĸ� ������ ���� ū �ǹ̰� �����ϴ�.
	�ٸ� �������� ��� nullptr�� ������ �� �ִ� ������ �ְ�,
	������ ��� const�� ���̸� ����� �ѱ� �� �ִ� ������ �ֽ��ϴ�.
	��, �Լ��� ������ ������ ����� �����ϸ� �˴ϴ�.
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