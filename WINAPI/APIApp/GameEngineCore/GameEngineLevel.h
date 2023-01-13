#pragma once
#include <list>
#include <map>

// 윈도우창에 보여지는 화면을 Level 또는 Sceen 이라고 한다. 
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
	// 화면을 보여줄 때 사용할 부분들을 로드한다.
	// GameEngineDirectory 클래스를 활용하여 디렉토리를 찾고, 경로를 만든 후 그 경로에 있는 파일 로드
	// 플레이어, 몬스터, 맵 등의 이미지, 사운드 
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	
	virtual void LevelChangeEnd(GameEngineLevel * _NextLevel) = 0;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;
	
private:
	// Order 값을 키값으로 하는 액터리스트를 저장한다. 
	std::map<int, std::list<GameEngineActor*>> Actors;
	
	// 업데이트와 렌더링은 기본적으로 델타타임을 받는다. 
	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);

	// 액터 생성 후 액터 로딩
	void ActorStart(GameEngineActor* _Actor, int _Order);

	// 렌더러 저장
	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
};