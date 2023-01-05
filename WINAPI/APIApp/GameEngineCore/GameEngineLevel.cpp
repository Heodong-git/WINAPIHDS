#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	// 메모리에서 제거 될 때 소유한 액터리스트를 모두 비워준다.
	// 레인지드포 문법 ranged for? 
	for (GameEngineActor* Actor : Actors)
	{
		// Actors.erase()
		if (nullptr != Actor)
		{
			delete Actor;
			Actor = nullptr;
		}
	}

	Actors.clear();
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}

	_Actor->Start();
}

void GameEngineLevel::ActorsUpdate()
{
	// 소유한 모든 액터의 업데이트
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Update();
	}
}

void GameEngineLevel::ActorsRender()
{
	// 소유한 모든 액터의 렌더링
	std::list<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::list<GameEngineActor*>::iterator EndIter = Actors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Render();
	}
}