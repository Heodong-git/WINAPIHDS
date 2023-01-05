#pragma once
#include <list>

// ������â�� �������� ȭ���� Level �Ǵ� Sceen �̶�� �Ѵ�. 
class GameEngineCore;
class GameEngineActor;
class GameEngineLevel
{
	friend GameEngineCore;
public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;
	 
	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// �������� ����� ���� ����
	template <typename ActorType>
	void CreateActor()
	{
		GameEngineActor* Actor = new ActorType;

		// ������ ������ �ʿ��� �κ� �ε�
		ActorStart(Actor);

		// Level �� �ڽ��� ������ Acotor ���� ����Ʈ ������ �ֱ� ������
		// �� ����Ʈ�� ������ ���͸� ���� 
		Actors.push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;
	
private:
	
	// Level �� ǥ���Ǵ� ��� ��ü�� 
	// GameEngineActor �� ��ӹޱ� ������ �� list �ϳ��� ������ ����
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();

	// ���� ���� �� ���� �ε�
	void ActorStart(GameEngineActor* _Actor);
};