#pragma once
#include <list>
#include <map>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// ������â�� �������� ȭ���� Level �Ǵ� Sceen �̶�� �Ѵ�. 
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineLevel : public GameEngineObject
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
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType;

		// ������ ������ �ʿ��� �κ� �ε�
		ActorStart(Actor , _Order);

		// ���� ���ο� ����
		// �ش��ϴ� Ű������, �����͸� �����Ѵ�.
		// �����Ͱ� ���� ���, �� Ű������ �����͸� �����Ѵ�.
		// �����Ͱ� ���� ���, �� Ű���� �ش��ϴ� �����͸� ���۷����� ��ȯ���ش�. 
		Actors[_Order].push_back(Actor);

		// ���͸� �����ϸ� ������ ������ ������Ÿ������ ĳ�����Ͽ� ��ȯ���ش�. 
		return dynamic_cast<ActorType*>(Actor);
	}

	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
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
	// ī�޶� ��ǥ
	float4 CameraPos = float4::Zero;

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