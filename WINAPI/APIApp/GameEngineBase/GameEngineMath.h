#pragma once
#include <math.h>
#include <cmath>
#include <string>
#include <vector>


// final 키워드 : 해당 키워드가 입력되어 있다면 그 클래스는 상속을 내리지 못한다.
class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);
	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

private:
	// 소멸자를 순수가상함수로 선언해줌으로써 
	// 이 클래스는 상속불가, 객체생성불가인 상태가 되어 
	// 오로지 변수를 사용하기 위한 용도로만 사용한다. 
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 Zero;
	static const float4 Null;

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// w 축만 왜 1.0 인지는 3d 때. ( 제발 3d까지 가자 ) 


	// float 타입의 x,y,z,w 축의 값을 static_cast로 int 타입으로 형변환하여 반환한다. 
	int ix() const  
	{
		return static_cast<int>(x);
	}

	int iy() const 
	{
		return static_cast<int>(y);
	}

	int iz() const  
	{
		return static_cast<int>(z);
	}

	int iw() const  
	{
		return static_cast<int>(w);
	}

	// 내부의 각 축의 절반의 값을 반환
	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}

	// 절반
	// half 함수를 호출하면 this 의 x, y, z 값을 절반으로 하여 그 값을 반환한다. 
	float4 half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.f, w };
	}

	// 모든 축의 값이 0인지 체크
	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	// 사이즈 ( length ) 
	float Size() const
	{
		// 삼각형의 밑변과 높이를 알기 때문에 빗변의 길이를 알 수 있다.
		// x * x + y * y = 빗변길이 제곱 
		return sqrtf(x * x + y * y);
	}

	// 정규화, 길이를 1로 만든다. 
	void Normalize()
	{
		// 방향을 구하고 그 방향 길이의 값을 1로 만든다. 
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}


	// 러프 
	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		// 1.5 + 0.5 * 2.5;
		return Start * (1.0f - Ratio) + (End * Ratio);
	}

	// 러프와 동일하지만 비율을 0 ~ 1로 제한
	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	// 오퍼레이터 *
	// const 객체도 이 함수를 호출 할 수 있도록 하기 위해 뒤에 const 키워드를 붙여준다. 
	float4 operator *(const float& _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;

		return Return;
	}

	float4 operator +(const float4 _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}


	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}


	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	// 오퍼레이터 +=
	float4 operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator *=(const float& _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}


	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}


	float4 operator /(const float4 _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}


	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}
};

// 클래스를 만든 이유.
// 좌표값을 하나의 변수로 표현할 수 있게 하고
// 방향고정값등을 편리하게 사용하기 위해서. 