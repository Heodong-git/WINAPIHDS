#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// 엔진에서 필수적으로 로드해야할 부분을 담당한다. 이미지, 사운드 리소스 등
// 전방선언을 통해 클래스의 포인터형을 사용할 수 있음, 객체생성하여 함수 호출등은 불가능하다. 
class GameEngineLevel;
class GameEngineCore
{
private:
	// 각각 게임실행, 실행중, 실행종료시 동작해야할 로직이 작성되서 입력하게 된다. 
	static void GlobalStart();
	static void GlobalUpdate();
	static void GlobalEnd();

public:
	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;

	// 프로그램을 동작시킨다. 
	void CoreStart(HINSTANCE _instance);

protected:
	// template 함수로 구현해줌으로써 함수호출시에
	// 원하는 데이터타입을 작성하여 호출하게 되면 맵에 해당하는 타입으로 저장해줄 수 있다. 
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		// 인자로 들어온 키값이 되는 문자열이 end() 가 아니라면
		// 이미 해당 키값으로 데이터가 저장되어 있다는 의미이다. 
		if (Levels.end() != Levels.find(_Name.data()))
		{
			// 인자로 들어온 문자열을 표시해주며 assert 처리
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		// 그게 아니라면 키값으로 데이터를 저장해준다. 
		// 인자로 들어온 레벨을 생성한다. 
		GameEngineLevel* Level = new LevelType();
		// 레벨을 생성한 후에는 해당하는 레벨에서 필요한 데이터를 로딩한다.
		LevelLoading(Level);
		// 데이터를 맵에 저장해준다. 
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	// 인자로 들어온 키값으로 장면을 변경시킨다. 
	void ChangeLevel(const std::string_view& _Name);

	// 상속을 받는 클래스는 반드시 이 함수들을 구현해주어야 한다. 
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// 키값을 사용해 탐색하는 부분에 특화되어 있음
	std::map<std::string, GameEngineLevel*> Levels;

	// 현재 선택되어 있는 메인레벨
	GameEngineLevel* MainLevel = nullptr;

	// Core 헤더에서 Level 헤더를 인클루드 하지 않기 위해 기능을 분리
	void LevelLoading(GameEngineLevel* _Level);
};

// 수정