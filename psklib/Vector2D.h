#pragma once
#include <cmath>

#include "tags.h"

// - 오차 허용치에 관한 네임스페이스
namespace __tol
{
	// - float 오차 허용치(Tolerance)
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

	// - Vector의 크기를 계산합니다.
	inline float Magnitude (void)
	{
		return std::sqrt (mX * mX + mY * mY); // sqrtf
	}

	// - 단위 벡터 변환 후 써야 함
	inline float DirToAngle(void)
	{
		return ((std::atan2(mY, mX) / pi) * 180.0f);
	}
	
	// - 단위 벡터(Unit Vector)로 정규화 하는 함수
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

	// - 방향을 반대로 가리키게 하는 함수
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

	// - 스칼라 곱 연산자
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

	// - 역벡터 연산자
	Vector2D operator-()
	{
		return Vector2D (-mX, -mY);
	}

	// - 벡터 뺄셈
	Vector2D operator-(const Vector2D& _other)
	{
		return Vector2D (mX - _other.mX, mY - _other.mY);
	}

	// - 내적 구하기
	float operator*(const Vector2D& _other)
	{
		return ((mX * _other.mX) + (mY * _other.mY));
	}

	// - 스칼라 곱
	Vector2D operator*(const float _scala)
	{
		return Vector2D(mX * _scala, mY * _scala);
	}

	const static Vector2D ZeroVector;

public:
#pragma region intger_vector
	// 형 변환을 위한 struct
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
