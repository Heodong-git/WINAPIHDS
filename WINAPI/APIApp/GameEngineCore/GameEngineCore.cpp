#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineLevel.h"

GameEngineCore* Core;

// ������ �ھ�Ŭ������ Start �Լ� ����
void GameEngineCore::GlobalStart()
{
	Core->Start();
}

// ������ �ھ�Ŭ������ Update �Լ� ����
void GameEngineCore::GlobalUpdate()
{
	// �ھ������Ʈ 
	Core->Update();

	// ���� �ھ��� ���η����� ���õǾ� ���� �ʴٸ� 
	// ������ �������� ���� ���̱� ������ assert ó��
	if (nullptr == Core->MainLevel)
	{
		MsgAssert("������ ���������� ���� ���·� �ھ �����߽��ϴ�");
		return;
	}
}

// ������ �ھ�Ŭ������ End �Լ� ����
void GameEngineCore::GlobalEnd()
{
	Core->End();
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
	// ������ ���� 
	GameEngineWindow::WindowCreate(_instance, "MainWindow", { 1360, 768 }, { 0, 0 });
	
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
	MainLevel = FindIter->second;
}