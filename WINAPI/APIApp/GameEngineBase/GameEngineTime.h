#pragma once
#include <chrono>
#include <Windows.h>

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

// FPS : 초당 프레임 값  
// DeltaTime : 프레임 당 걸리는 시간  

// 게임에서 사용할 DeltaTime를 구하고 사용하기 위해서