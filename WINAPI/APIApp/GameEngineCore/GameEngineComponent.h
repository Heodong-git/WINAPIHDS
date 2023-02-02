#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// �߰����� ��ɿ� ���Ǵ� Ŭ���� ex) ������, �浹ü ���� ������Ʈ��� �Ѵ�.
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

	// offset �� ��������
	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	// ������Ʈ�� x,y �� ũ�� ����
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

	// �ڽ��� ������ ���͹�ȯ
	GameEngineActor* GetActor();

	// ������ ������ġ + ������Ʈ�� ��������ġ�� ���� ���� ��ȯ�Ѵ�. 
	float4 GetActorPlusPos();

protected:

private:
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;

};

