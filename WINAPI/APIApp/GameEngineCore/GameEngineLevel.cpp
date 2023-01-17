#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRender.h"
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

	// 생성한 액터의 Level = this
	_Actor->Level = this;
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

// 액터업데이트
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	{
		// 키값 : int , 데이터 : GameEngineActor* 를 저장하는 리스트
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
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				// 액터가 만들어진 이후부터 화면에 살아있는 시간을 계산한다. 
				Actor->LiveTime += _DeltaTime;
				Actor->Update(_DeltaTime);
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
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->LateUpdate(_DeltaTime);
			}
		}
	}

}

// 액터렌더
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			for (GameEngineRender* Renderer : RenderList)
			{
				// Actors.erase()
				if (nullptr == Renderer)
				{
					continue;
				}

				Renderer->Render(_DeltaTime);
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
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->Render(_DeltaTime);
			}
		}
	}
}

// 렌더러 생성후 호출하여 리스트에 추가하는 함수
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("nullptr인 랜더를 랜더링 그룹속에 넣으려고 했습니다.");
	}

	// 먼저 이미 들어가있을수도 있다.
	// map 의 문법 
	// 데이터가 존재하지 않는다면 추가한다.
	// 데이터가 이미 있다면, 그녀석을 반환한다. 
	Renders[_Render->GetOrder()].push_back(_Render);
}