#pragma once

// final 키워드 : 해당 키워드가 입력되어 있다면 그 클래스는 상속을 내리지 못한다.
class GameEngineMath final
{
public:
	static const float PIE;
	static const float PIE2;

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

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
	// w 축만 왜 1.0 인지는 3d 때. ( 제발 3d까지 가자 ) 


	// float 타입의 x,y,z,w 축의 값을 static_cast로 int 타입으로 형변환하여 반환한다. 
	int ix() {
		return static_cast<int>(x);
	}

	int iy() {
		return static_cast<int>(y);
	}

	int iz() {
		return static_cast<int>(z);
	}

	int iw() {
		return static_cast<int>(w);
	}
};