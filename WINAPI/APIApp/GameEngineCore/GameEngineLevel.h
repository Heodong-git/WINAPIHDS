#pragma once
#include <list>
#include <map>

// ������â�� �������� ȭ���� Level �Ǵ� Sceen �̶�� �Ѵ�. 
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineLevel
{
	friend GameEngineCore;
	friend GameEngineRender;

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
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType;

		// ������ ������ �ʿ��� �κ� �ε�
		ActorStart(Actor , _Order);

		// ���� ���ο� ����
		// �ش��ϴ� Ű������, �����͸� �����Ѵ�.
		// �����Ͱ� ���� ���, �� Ű������ �����͸� �����Ѵ�.
		// �����Ͱ� ���� ���, �� Ű���� �ش��ϴ� �����͸� ���۷����� ��ȯ���ش�. 
		Actors[_Order].push_back(Actor);
	}

protected:
	// ȭ���� ������ �� ����� �κе��� �ε��Ѵ�.
	// GameEngineDirectory Ŭ������ Ȱ���Ͽ� ���丮�� ã��, ��θ� ���� �� �� ��ο� �ִ� ���� �ε�
	// �÷��̾�, ����, �� ���� �̹���, ���� 
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	
	virtual void LevelChangeEnd(GameEngineLevel * _NextLevel) = 0;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;
	
private:
	// Order ���� Ű������ �ϴ� ���͸���Ʈ�� �����Ѵ�. 
	std::map<int, std::list<GameEngineActor*>> Actors;
	
	// ������Ʈ�� �������� �⺻������ ��ŸŸ���� �޴´�. 
	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);

	// ���� ���� �� ���� �ε�
	void ActorStart(GameEngineActor* _Actor, int _Order);

	// ������ ����
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
};