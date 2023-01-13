#include "GameEngineTime.h"

// static 변수 구현
GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime()
{
	// 시작할때 1번만 정하면 된다.
	QueryPerformanceFrequency(&Second);

	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	// 현재까지의 값을 받아온다. 
	QueryPerformanceCounter(&Current);

	// 현재시간값 - 이전시간값
	// 틱당 걸리는 시간 
	Tick = Current.QuadPart - Prev.QuadPart;
                               
	// 델타타임 = 현재시간 - 이전시간 / 기준시간
	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	// 델타타임을 구해주었기 때문에 
	// 이전 시간값 = 현재시간 값이 되고
	// 다음 프레임에서 같은방식으로 계산하게 된다.
	Prev.QuadPart = Current.QuadPart;

	// 대세를 따른다 델타타임은 float 타입사용. 
	floatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return floatDeltaTime;
}
