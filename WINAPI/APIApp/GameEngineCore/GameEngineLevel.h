#pragma once
#include <list>

// 설명 : 게임 내부의 화면, 장면을 Level 또는 Sceen 이라고 한다. 
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

	// 레벨에서 사용할 액터클래스를 생성한다.
	template <typename ActorType>
	void CreateActor()
	{
		// 인자로들어온 타입으로 액터클래스 동적할당
		GameEngineActor* Actor = new ActorType;

		// 액터가 만들어졌기 때문에 액터의 Start 함수를 호출하여 액터의이미지등 필요한 부분을 세팅한다.
		// 마찬가지로 헤더에서 액터클래스를 include 하지 않기 위해 기능분리 
		ActorStart(Actor);

		// 액터를 만들고 초기화해주었기 때문에 
		// Level 이 소유한 액터 리스트에 추가해준다.
		Actors.push_back(Actor);
	}

protected:
	// 장면 진입시 
	virtual void Loading() = 0;
	virtual void Update() = 0;
	
private:
	// 화면에 등장하는 모든 것들에 상속을 내려줄 클래스이기 때문에
	// 이 자료형 하나로 모두 표현할 수 있게 된다.
	std::list<GameEngineActor*> Actors;

	void ActorsUpdate();
	void ActorsRender();

	void ActorStart(GameEngineActor* _Actor);
};