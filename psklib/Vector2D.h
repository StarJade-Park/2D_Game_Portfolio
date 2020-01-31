#pragma once
#include <cmath>

#include "tags.h"

// - ���� ���ġ�� ���� ���ӽ����̽�
namespace __tol
{
	// - float ���� ���ġ(Tolerance)
	constexpr float ftol = 0.0001f;
}

// - Float 2D Vector
class Vector2D
{
public:
	Vector2D (void)
		: mX(0.0f)
		, mY(0.0f)
	{
		EMPTY_STATEMENT;
	}

	Vector2D (float _x, float _y)
		: mX (_x)
		, mY (_y)
	{
		EMPTY_STATEMENT;
	}

	~Vector2D () = default;

	// - Vector�� ũ�⸦ ����մϴ�.
	inline float Magnitude (void)
	{
		return std::sqrt (mX * mX + mY * mY); // sqrtf
	}

	// - ���� ���� ��ȯ �� ��� ��
	inline float DirToAngle(void)
	{
		return ((std::atan2(mY, mX) / pi) * 180.0f);
	}
	
	// - ���� ����(Unit Vector)�� ����ȭ �ϴ� �Լ�
	void Normalize (void)
	{
		float magnitude = Magnitude ();

		if (__tol::ftol >= magnitude)
		{
			magnitude = 1.0f;
		}

		mX /= magnitude;
		mY /= magnitude;

		if (__tol::ftol >= fabs (mX))
		{
			mX = 0.0f;
		}

		if (__tol::ftol >= fabs (mY))
		{
			mY = 0.0f;
		}
	}

	// - ������ �ݴ�� ����Ű�� �ϴ� �Լ�
	void Reverse (void)
	{
		mX = -mX;
		mY = -mY;
	}

	Vector2D& operator+=(const Vector2D& _other)
	{
		mX += _other.mX;
		mY += _other.mY;

		return *this;
	}

	Vector2D& operator-=(const Vector2D& _other)
	{
		mX -= _other.mX;
		mY -= _other.mY;

		return *this;
	}

	// - ��Į�� �� ������
	Vector2D& operator*=(const float _scala)
	{
		mX *= _scala;
		mY *= _scala;

		return *this;
	}

	Vector2D& operator/=(const float _scala)
	{
		mX /= _scala;
		mY /= _scala;

		return *this;
	}

	// - ������ ������
	Vector2D operator-()
	{
		return Vector2D (-mX, -mY);
	}

	// - ���� ����
	Vector2D operator-(const Vector2D& _other)
	{
		return Vector2D (mX - _other.mX, mY - _other.mY);
	}

	// - ���� ���ϱ�
	float operator*(const Vector2D& _other)
	{
		return ((mX * _other.mX) + (mY * _other.mY));
	}

	// - ��Į�� ��
	Vector2D operator*(const float _scala)
	{
		return Vector2D(mX * _scala, mY * _scala);
	}

	const static Vector2D ZeroVector;

public:
#pragma region intger_vector
	// �� ��ȯ�� ���� struct
	typedef struct __tagIVector2D
	{
	public:
		int mX;
		int mY;
	} IVector2D;

	IVector2D ToInt ()
	{
		IVector2D convertToInt;
		convertToInt.mX = (int)mX;
		convertToInt.mY = (int)mY;
		return convertToInt;
	}

	int XToInt( )
	{
		return (int)mX;
	}

	int YToInt( )
	{
		return (int)mY;
	}

	IVector2D ToHalfInt( )
	{
		IVector2D convertToInt;
		convertToInt.mX = (int)(mX * 0.5f);
		convertToInt.mY = (int)(mY * 0.5f);
		return convertToInt;
	}
#pragma endregion

public:
	float mX;
	float mY;

private:
	static const float pi;
};
