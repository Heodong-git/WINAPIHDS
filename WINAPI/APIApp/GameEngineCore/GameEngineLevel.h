#pragma once
#include <list>

// 윈도우창에 보여지는 화면을 Level 또는 Sceen 이라고 한다. 
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

	// 레벨에서 사용할 액터 생성
	template <typename ActorType>
	void CreateActor()
	{
		GameEngineActor* Actor = new ActorType;

		// 생성한 액터의 필요한 부분 로딩
		ActorStart(Actor);

		// Level 은 자신이 소유한 Acotor 들의 리스트 가지고 있기 때문에
		// 그 리스트에 생성한 액터를 저장 
		Actors.push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;
	
private:
	
	// Level 에 표현되는 모든 물체는 
	// GameEngineActor 를 상속받기 때문에 이 list 하나로 관리가 가능
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();

	// 액터 생성 후 액터 로딩
	void ActorStart(GameEngineActor* _Actor);
};