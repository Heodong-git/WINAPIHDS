#pragma once

// ���� : ���ӳ��ο��� �����̴� ��ü�� , Level �� ���������� Ÿ��Ʋ�̹���, ����ϱ� ��ư ���� ���Ѵ�. 
class GameEngineActor
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:

private:

};

