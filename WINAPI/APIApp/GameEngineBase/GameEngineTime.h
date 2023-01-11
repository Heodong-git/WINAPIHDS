#pragma once
#include <chrono>
#include <Windows.h>

// ũ�γ븦 ����Ϸ��� ������, ���� �츮�� ���� ����� �κ��� �־ 
// window �� ��� ���

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

	// �� ���̿� ������ ���� �ð��� ��� ����Դϴ�.

	float TimeCheckEnd();

protected:


private:
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
};

