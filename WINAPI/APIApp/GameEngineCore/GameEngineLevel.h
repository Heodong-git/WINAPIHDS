#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCollision.h>

// ������â�� �������� ȭ���� Level �Ǵ� Sceen �̶�� �Ѵ�. 
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollsion;
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;
	 
	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// ����׿� ���� ����ġ
	static void DebugRenderSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}

	float4 GetMousePos();
	float4 GetMousePosToCamera();


	// ���ͻ����� Order Ÿ���� ���ڷ� �޴´�. 
	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

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

	// ���ϴ� Ÿ���� ���ڷ� �־��ָ� �ش��ϴ� Ÿ���� �迭�� ��ȯ�Ѵ�. 
	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	// ������ ������ ������ ���ϴ� Ÿ���� ��� �޾ƿ� �� ����. 
	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		// ���ο��� ���ο� vector ����
		std::vector<GameEngineActor*> Result;

		// ���͸���Ʈ�� ����ִ� �迭 ����ü�� �޾ƿ´�. (���۷���)  
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		
		// ���� ������ �迭�� ������ �޾ƿ� �迭�� ũ�⸸ŭ �ø���. 
		Result.reserve(Group.size());

		// �޾ƿ� �����͸� push_back 
		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		// �����͸� �������� vector �� ��ȯ���ش�. 
		return Result;
	}

	static void DebugTextPush(const std::string& _DebugText)
	{
		DebugTexts.push_back(_DebugText);
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
	static bool IsDebugRender;

	// ī�޶� ��ǥ
	float4 CameraPos = float4::Zero;

	static float4 TextOutStart;
	static std::vector<std::string> DebugTexts;

	// Order ���� Ű������ �ϴ� ���͸���Ʈ�� �����Ѵ�. 
	std::map<int, std::list<GameEngineActor*>> Actors;
	
	// ������Ʈ�� �������� �⺻������ ��ŸŸ���� �޴´�. 
	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);

	// ���� ���� �� ���� �ε�
	void ActorStart(GameEngineActor* _Actor, int _Order);

	// ������ ����
	std::map<int, std::list<GameEngineRender*>> Renders;
	// �ʿ� ������ �߰�
	void PushRender(GameEngineRender* _Render);

	// �浹ü ����
	std::map<int, std::list<GameEngineCollision*>> Collisions;
	// �ʿ� �浹ü �߰�  
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);

	// ���������� ����̱� ������ private���� �д�.
	void Release();
};