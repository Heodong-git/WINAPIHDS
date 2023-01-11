#pragma once
#include <chrono>
#include <Windows.h>

// 크로노를 사용하려고 했으나, 현재 우리가 배우긴 어려운 부분이 있어서 
// window 의 기능 사용

class GameEngineTime
{
public:
	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void TimeCheckStart();

	// 이 사이에 벌어진 일의 시간을 재는 기능입니다.

	float TimeCheckEnd();

protected:


private:
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
};

