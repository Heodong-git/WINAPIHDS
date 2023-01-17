#pragma once
#include <Windows.h>
#include <map>
#include <string_view>
#include <GameEngineBase/GameEngineDebug.h>

// 전방선언을 통해 클래스의 포인터형을 사용할 수 있음, 객체생성하여 함수 호출등은 불가능
// 엔진에서 필수적으로 로드해야할 부분을 담당
class GameEngineLevel;
class GameEngineCore
{
private:
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

	// 프로그램을 동작
	void CoreStart(HINSTANCE _instance);
	
	// 인자로 들어온 키값으로 장면을 변경한다. 
	void ChangeLevel(const std::string_view& _Name);

	static GameEngineCore* GetInst();
protected:
	// 템플릿함수로 작성하여 함수호출시 데이터타입을 입력받는다. 
	// 내부에서 상속받은 클래스들이 동적할당 후 업캐스팅 되어 부모클래스 타입 포인터 변수에
	// 저장되기 때문에 상속받지 않은 클래스들이 입력되게 된다면 에러.
	template<typename LevelType>
	void CreateLevel(const std::string_view& _Name)
	{
		// 인자로 들어온 키값이 되는 문자열이 end() 가 아니라면
		// 이미 해당 키값으로 데이터가 저장되어 있다는 의미이다. 
		if (Levels.end() != Levels.find(_Name.data()))
		{
			// 인자로 들어온 문자열을 표시해주며 assert
			std::string Name = _Name.data();
			MsgAssert(Name + "이미 존재하는 이름의 레벨을 만들려고 했습니다");
			return;
		}

		// 키값으로 데이터를 저장해준다. 
		GameEngineLevel* Level = new LevelType();
		// 레벨 생성 후 해당 레벨에 필요한 데이터 로딩
		LevelLoading(Level);
		// 생성한 레벨을 저장
		Levels.insert(std::make_pair(_Name.data(), Level));
	}

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}
	
	// 상속받는 클래스는 반드시 이 함수들을 구현해야 한다. 
	// 부모클래스가 추상클래스일 경우 , 자식클래스에서 구현하지 않는다면
	// 자식클래스도 추상클래스가 되어 객체를 생성하지 못하게 된다. 
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

private:
	// 문자열 키값으로 레벨포인터 저장
	std::map<std::string, GameEngineLevel*> Levels;
	GameEngineLevel* NextLevel = nullptr;
	GameEngineLevel* MainLevel = nullptr;
	
	// 레벨로딩함수 (순환참조방지, 기능분리)
	void LevelLoading(GameEngineLevel* _Level);

	bool IsDebugValue = false;
};