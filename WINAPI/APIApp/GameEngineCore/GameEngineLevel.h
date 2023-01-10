#pragma once
#include <list>
#include <map>

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
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType;

		// 생성한 액터의 필요한 부분 로딩
		ActorStart(Actor , _Order);

		// 맵의 새로운 문법
		// 해당하는 키값으로, 데이터를 저장한다.
		// 데이터가 없을 경우, 그 키값으로 데이터를 저장한다.
		// 데이터가 있을 경우, 그 키값에 해당하는 데이터를 레퍼런스로 반환해준다. 
		Actors[_Order].push_back(Actor);
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;
	
private:
	// Order 값을 키값으로 하는 액터리스트를 저장한다. 
	std::map<int, std::list<GameEngineActor*>> Actors;

	void ActorsUpdate();
	void ActorsRender();

	// 액터 생성 후 액터 로딩
	void ActorStart(GameEngineActor* _Actor, int _Order);
};