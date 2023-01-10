#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineDebug.h>

// 여기서부터 주석 다시 정리하면서 코드살피기

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	
	// ranged for (레인지드 포) 
	// 범위기반
	// 저장된 데이터타입 : 데이터리스트명
	// 문법 사용시 주의점 : 반복실행시 데이터를 하나만 지운다거나 하는 행동을 하면 안됨!! 
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		// UpdateGroup.second = 액터리스트 
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		// 액터리스트에 저장되어 있는 모든 액터를 제거한다. 
		for (GameEngineActor* Actor : ActorList)
		{
			// Actors.erase()
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}

	Actors.clear();
}

void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}

	_Actor->SetOrder(_Order);
	_Actor->Start();
}

void GameEngineLevel::ActorsUpdate()
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		// 시작노드가 끝노드가 아닐때 까지 ++하여 순회 
		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			// 레인지드포  
			// 저장된 데이터타입 : 자료구조이름
			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor)
				{
					continue;
				}

				Actor->Update();
			}
		}
	}

	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor)
				{
					continue;
				}

				Actor->LateUpdate();
			}
		}
	}
}

void GameEngineLevel::ActorsRender()
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor)
				{
					continue;
				}

				Actor->Render();
			}
		}
	}
}