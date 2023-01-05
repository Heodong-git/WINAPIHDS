#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	
	// ranged for (레인지드 포) 
	// 범위기반
	// 데이터타입 : 데이터리스트명
	// 문법 사용시 주의점 : 반복실행시 데이터를 하나만 지운다거나 하는 행동을 하면 안됨!! 
	//for (GameEngineActor* Actor : Actors)
	//{
	//	// Actors.erase()
	//	if (nullptr != Actor)
	//	{
	//		delete Actor;
	//		Actor = nullptr;
	//	}
	//}

	// iterator 를 사용한 제거 연습
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