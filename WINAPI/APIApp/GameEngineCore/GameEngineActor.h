#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

// 어떠한 Level에 속해있는 화면에 표현되는 모든것 --- Actor
class GameEngineLevel;
class GameEngineActor
{
	// GameEngineLevl 에서 GameEngineActor 클래스 내부에 접근 가능
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// 위치반환
	float4 GetPos()
	{
		return Pos;
	}

	// 위치세팅
	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// 위치이동, 기존의 자신의 좌표 + 인자로 들어온 값 
	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

protected:
	// 클래스 생성 후 바로 해주어야할 일
	virtual void Start() {}

	// 키입력 + 논리적인 연산 수행
	virtual void Update() {}

	// 연산 수행 후 화면에 출력되는 부분을 수행 
	virtual void Render() {}

private:
	// 좌표
	float4 Pos = { 0.0f, 0.0f };
};

