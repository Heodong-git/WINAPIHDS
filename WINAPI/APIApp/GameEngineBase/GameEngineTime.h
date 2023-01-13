#pragma once
#include <chrono>
#include <Windows.h>

// 크로노를 사용하려고 했으나, 현재 우리가 배우긴 어려운 부분이 있어서 
// window 의 기능 사용

class GameEngineTime
{
public:
	static GameEngineTime GlobalTime;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	void Reset();

	float TimeCheck();

	float GetFloatDeltaTime()
	{
		return floatDeltaTime;
	}

protected:


private:
	// 현재시간 - 이전시간
	__int64 Tick = 0;
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;
};

