#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineLevel.h"


GameEngineCore* Core;

// 생성된 코어클래스의 Start 함수 동작
void GameEngineCore::GlobalStart()
{
	Core->Start();
}

// 생성된 코어클래스의 Update 함수 동작
void GameEngineCore::GlobalUpdate()
{
	// 코어 업데이트 ( 필요한 연산 ) 
	Core->Update();

	// 만약 코어의 메인레벨이 선택되어 있지 않다면 
	// 레벨을 선택하지 않은 것이기 때문에 assert 처리
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("레벨을 지정해주지 않은 상태로 코어를 실행했습니다");
		return;
	}

	// 현재 레벨이 소유한 액터연산
	Core->MainLevel->ActorsUpdate();
	// 더블버퍼 클리어
	GameEngineWindow::DoubleBufferClear();
	// 연산된 값을 토대로 더블버퍼에 출력
	Core->MainLevel->ActorsRender();
	// 더블버퍼에 이미지가 모두 그려졌기 때문에 백버퍼에 옮겨그려준다. 
	GameEngineWindow::DoubleBufferRender();
	
}

// 생성된 코어클래스의 End 함수 동작
void GameEngineCore::GlobalEnd()
{
	Core->End();

	// 게임이 종료될 때 리소스가 생성한 이미지들을 모두 제거해준다. 
	GameEngineResources::GetInst().Relase();
}

// 코어가 생성될 때 릭체크 함수 동작 + 생성된 코어의 주소값을 가진다. 
GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	// 이 때 대입되는 this 는 
	// 프로그램 실행시 데이터 영역에 메모리가 만들어지는 MegaManCore가 된다. 
	Core = this;
}

// 코어 소멸자에서는 맵에 저장되어 있는 동적할당된 객체들을 모두 제거한다. 
GameEngineCore::~GameEngineCore()
{
	// StartIter = 레벨이 저장되어 있는 클래스 객체의 begin();
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	// EndIter = 레벨이 저장되어 있는 클래스 객체의 end();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	// StartIter 가 EndIter가 아니라면 반복하여 객체들을 제거한다. 
	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	// 작업이 완료 되었다면 맵 clear 
	Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	// 윈도우 생성 
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1360.0f, 768.0f }, { 0, 0 });
	
	// 윈도우 루프
	// 이러한 방식을 callback 방식이라고 하며 
	// 외부의 함수를 원하시는 시점, 이벤트 발생시 호출하는 방식이다. 
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, 
								 GameEngineCore::GlobalUpdate, 
							     GameEngineCore::GlobalEnd);
}

// 장면변경
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	// 인자로 들어온 키값으로 저장된 데이터가 있는지 확인한다. 
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	// FinIter가 nullptr 이라면 입력된 키값으로 저장되어 있는 Level 이 존재하지 않는 것
	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "존재하지 않는 레벨을 실행시키려고 했습니다");
		return;
	}

	// 그게 아니라면 메인레벨을 저장되어 있는 레벨로 지정해준다.
	MainLevel = FindIter->second;
}

// 헤더에 다른 헤더를 인클루드 하지 않기 위해 기능을 분리
void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr 인 레벨을 로딩하려고 했습니다.");
		return;
	}

	// GameEngineLevel 클래스의 friend class 로 Core를 선언하여 
	// Core 클래스에서는 Level 클래스의 내부에 접근이 가능하도록 작성해준다.
	_Level->Loading();
}
