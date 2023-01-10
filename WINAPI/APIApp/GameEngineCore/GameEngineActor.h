#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>

// ��� Level�� �����ִ� ȭ�鿡 ǥ���Ǵ� ���� --- Actor
class GameEngineLevel;
class GameEngineActor
{
	// GameEngineLevl ���� GameEngineActor Ŭ���� ���ο� ���� ����
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

	// ��ġ��ȯ
	float4 GetPos()
	{
		return Pos;
	}

	// ��ġ����
	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// ��ġ�̵�, ������ �ڽ��� ��ǥ + ���ڷ� ���� �� 
	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

protected:
	// Ŭ���� ���� �� �ٷ� ���־���� ��
	virtual void Start() {}

	// Ű�Է� + ������ ���� ����
	virtual void Update() {}

	// �����������, ����ϱ� �� �̰� �� ����ϳ�? ��� �����غ�����.
	virtual void LateUpdate() {}

	// ���� ���� �� ȭ�鿡 ��µǴ� �κ��� ���� 
	virtual void Render() {}

private:
	int	Order;		// ������Ʈ, ������ ���� ���� ���� ���� ���� ���� 
	float4 Pos = { 0.0f, 0.0f };

	void SetOrder(int _Order)
	{
		Order = _Order;
	}
};

