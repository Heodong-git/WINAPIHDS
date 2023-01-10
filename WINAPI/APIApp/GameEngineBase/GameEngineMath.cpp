#include "GameEngineMath.h"

// 파이
const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
// 2파이는 파이 * 2 
const float GameEngineMath::PIE2 = PIE * 2.0f;

// float4 클래스 내부에 선언된 static 변수 구현
// 멤버변수들이 모두 public 이기 때문에 리스트이니셜라이저 문법을 통해 초기화 가능
const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Down = { 0.0f, 1.0f, 0.0f, 1.0f };

// 2d때는 쓸일이 없을것이다.
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back = { 0.0f, 0.0f, -1.0f, 1.0f };

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Null = { 0.0f, 0.0f, 0.0f, 0.0f };