#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 추가적인 기능에 사용되는 클래스 ex) 렌더러, 충돌체 등을 컴포넌트라고 한다.
class GameEngineActor;
class GameEngineComponent : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	// offset 과 같은개념
	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	// 컴포넌트의 x,y 축 크기 설정
	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	inline float4 GetPosition()
	{
		return Position;
	}

	inline float4 GetScale()
	{
		return Scale;
	}

	// 자신을 소유한 액터반환
	GameEngineActor* GetActor();

	// 오너의 현재위치 + 컴포넌트의 오프셋위치를 더한 값을 반환한다. 
	float4 GetActorPlusPos();

protected:

private:
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;

};

