#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	
	// ranged for (�������� ��) 
	// �������
	// ������Ÿ�� : �����͸���Ʈ��
	// ���� ���� ������ : �ݺ������ �����͸� �ϳ��� ����ٰų� �ϴ� �ൿ�� �ϸ� �ȵ�!! 
	//for (GameEngineActor* Actor : Actors)
	//{
	//	// Actors.erase()
	//	if (nullptr != Actor)
	//	{
	//		delete Actor;
	//		Actor = nullptr;
	//	}
	//}

	// iterator �� ����� ���� ����
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();
	
	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != *StartIter)
		{
			delete *StartIter;
			*StartIter = nullptr;
		}
	}

	Actors.clear();
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr ���͸� Start�Ϸ��� �߽��ϴ�.");
		return;
	}

	_Actor->Start();
}

void GameEngineLevel::ActorsUpdate()
{
	// ������ ��� ������ ������Ʈ
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Update();
	}
}

void GameEngineLevel::ActorsRender()
{
	// ������ ��� ������ ������
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Render();
	}
}