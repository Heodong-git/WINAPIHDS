#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineLevel.h"
#include "GameEngineResources.h"
#include <GameEngineBase/GameEngineTime.h>

GameEngineCore* Core;

GameEngineCore* GameEngineCore::GetInst()
{
	return Core;
}

// ������ �ھ�Ŭ������ Start �Լ� ����
void GameEngineCore::GlobalStart()
{
	Core->Start();
	
	// �ھŸƮ �Լ� ȣ��ÿ� �ð�����
	GameEngineTime::GlobalTime.Reset();
}

// ������ �ھ�Ŭ������ Update �Լ� ����
void GameEngineCore::GlobalUpdate()
{
	// ������Ʈ�� ���� �� �� �ٷ� ����
	// NextLevel �� nullptr �� �ƴ϶�� ChangeLevel �ȴٴ� ���̴�. 
	if (nullptr != Core->NextLevel)
	{
		GameEngineLevel* PrevLevel = Core->MainLevel;
		GameEngineLevel* NextLevel = Core->NextLevel;

		// ���� ������ nullptr �� �ƴ϶��
		if (nullptr != PrevLevel)
		{
			// ���������� ������ �۾��� ����
			PrevLevel->LevelChangeEnd(NextLevel);
		}

		// ������ ���� ������ �����Ѵ�. 
		Core->MainLevel = NextLevel;
		// ���������� nullptr �� �ʱ�ȭ
		Core->NextLevel = nullptr;

		// ���������� nullptr �� �ƴ϶�� ������ ����ȴٴ� �ǹ�
		if (nullptr != NextLevel)
		{
			// ���������� ����ɶ� �ؾ��� �۾��� �����Ѵ�. 
			NextLevel->LevelChangeStart(PrevLevel);
		}
	}

	// ���������� ���۽ÿ� ��ŸŸ���� ���Ѵ�.
	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	// �ٸ� Ŭ�������� Update �� Render�� �̷������ ���� 
	// KeyUpdate �� ���� ���� Ű�� ���ȴ��� üũ�ϰ� 
	// ���� ���꿡�� �ݿ��Ѵ�. 
	GameEngineInput::Update(TimeDeltaTime);

	// �ھ� ������Ʈ ( �ʿ��� ���� ) 
	Core->Update();

	// ���� �ھ��� ���η����� ���õǾ� ���� �ʴٸ� 
	// ������ �������� ���� ���̱� ������ assert ó��
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
		return;
	}

	// ���η����� ������Ʈ�� ���� ���� 
	Core->MainLevel->Update(TimeDeltaTime);
	// ���� ������ ������ ���Ϳ���
	Core->MainLevel->ActorsUpdate(TimeDeltaTime);
	// ������� Ŭ����
	GameEngineWindow::DoubleBufferClear();
	// ����� ���� ���� ������ۿ� ���
	Core->MainLevel->ActorsRender(TimeDeltaTime);
	// ������ۿ� �̹����� ��� �׷����� ������ ����ۿ� �Űܱ׷��ش�. 
	GameEngineWindow::DoubleBufferRender();
	// ����, �������� ��� �Ϸ� �ƴٸ� �޸𸮿��� ���ŵ� �༮���� �����ش�. 
	Core->MainLevel->Release();
}

// ������ �ھ�Ŭ������ End �Լ� ����
void GameEngineCore::GlobalEnd()
{
	Core->End();

	// ������ ����� �� ���ҽ��� ������ �̹������� ��� �������ش�. 
	GameEngineResources::GetInst().Release();
}

// �ھ ������ �� ��üũ �Լ� ���� + ������ �ھ��� �ּҰ��� ������. 
GameEngineCore::GameEngineCore()
{
	GameEngineDebug::LeakCheck();

	// �� �� ���ԵǴ� this �� 
	// ���α׷� ����� ������ ������ �޸𸮰� ��������� MegaManCore�� �ȴ�. 
	Core = this;
}

// �ھ� �Ҹ��ڿ����� �ʿ� ����Ǿ� �ִ� �����Ҵ�� ��ü���� ��� �����Ѵ�. 
GameEngineCore::~GameEngineCore()
{
	// StartIter = ������ ����Ǿ� �ִ� Ŭ���� ��ü�� begin();
	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	// EndIter = ������ ����Ǿ� �ִ� Ŭ���� ��ü�� end();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	// StartIter �� EndIter�� �ƴ϶�� �ݺ��Ͽ� ��ü���� �����Ѵ�. 
	for (size_t i = 0; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	// �۾��� �Ϸ� �Ǿ��ٸ� �� clear 
	Levels.clear();
}

void GameEngineCore::CoreStart(HINSTANCE _instance)
{
	// ���콺 ��,��Ŭ�� Ű����
	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	// ������ ���� 
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1280.0f, 960.0f }, { 0, 0 });
	
	// ������ ����
	// �̷��� ����� callback ����̶�� �ϸ� 
	// �ܺ��� �Լ��� ���Ͻô� ����, �̺�Ʈ �߻��� ȣ���ϴ� ����̴�. 
	GameEngineWindow::WindowLoop(GameEngineCore::GlobalStart, 
								 GameEngineCore::GlobalUpdate, 
							     GameEngineCore::GlobalEnd);
}

// ��麯��
void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	// ���ڷ� ���� Ű������ ����� �����Ͱ� �ִ��� Ȯ���Ѵ�. 
	std::map<std::string, GameEngineLevel*>::iterator FindIter = Levels.find(_Name.data());

	// FinIter�� nullptr �̶�� �Էµ� Ű������ ����Ǿ� �ִ� Level �� �������� �ʴ� ��
	if (FindIter == Levels.end())
	{
		std::string Name = _Name.data();
		MsgAssert(Name + "�������� �ʴ� ������ �����Ű���� �߽��ϴ�");
		return;
	}

	// �װ� �ƴ϶�� ���η����� ����Ǿ� �ִ� ������ �������ش�.
	NextLevel = FindIter->second;
}



// ����� �ٸ� ����� ��Ŭ��� ���� �ʱ� ���� ����� �и�
void GameEngineCore::LevelLoading(GameEngineLevel* _Level)
{
	if (nullptr == _Level)
	{
		MsgAssert("nullptr �� ������ �ε��Ϸ��� �߽��ϴ�.");
		return;
	}

	// GameEngineLevel Ŭ������ friend class �� Core�� �����Ͽ� 
	// Core Ŭ���������� Level Ŭ������ ���ο� ������ �����ϵ��� �ۼ����ش�.
	_Level->Loading();
}
