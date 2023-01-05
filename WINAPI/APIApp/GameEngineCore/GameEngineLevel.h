#pragma once
#include <list>

// ���� : ���� ������ ȭ��, ����� Level �Ǵ� Sceen �̶�� �Ѵ�. 
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

	// �������� ����� ����Ŭ������ �����Ѵ�.
	template <typename ActorType>
	void CreateActor()
	{
		// ���ڷε��� Ÿ������ ����Ŭ���� �����Ҵ�
		GameEngineActor* Actor = new ActorType;

		// ���Ͱ� ��������� ������ ������ Start �Լ��� ȣ���Ͽ� �������̹����� �ʿ��� �κ��� �����Ѵ�.
		// ���������� ������� ����Ŭ������ include ���� �ʱ� ���� ��ɺи� 
		ActorStart(Actor);

		// ���͸� ����� �ʱ�ȭ���־��� ������ 
		// Level �� ������ ���� ����Ʈ�� �߰����ش�.
		Actors.push_back(Actor);
	}

protected:
	// ��� ���Խ� 
	virtual void Loading() = 0;
	virtual void Update() = 0;
	
private:
	// ȭ�鿡 �����ϴ� ��� �͵鿡 ����� ������ Ŭ�����̱� ������
	// �� �ڷ��� �ϳ��� ��� ǥ���� �� �ְ� �ȴ�.
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();

	void ActorStart(GameEngineActor* _Actor);
};