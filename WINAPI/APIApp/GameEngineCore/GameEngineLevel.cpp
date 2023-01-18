#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineDebug.h>

// ���⼭���� �ּ� �ٽ� �����ϸ鼭 �ڵ���Ǳ�

GameEngineLevel::GameEngineLevel()
{
}

GameEngineLevel::~GameEngineLevel()
{
	
	// ranged for (�������� ��) 
	// �������
	// ����� ������Ÿ�� : �����͸���Ʈ��
	// ���� ���� ������ : �ݺ������ �����͸� �ϳ��� ����ٰų� �ϴ� �ൿ�� �ϸ� �ȵ�!! 
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		// UpdateGroup.second = ���͸���Ʈ 
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		// ���͸���Ʈ�� ����Ǿ� �ִ� ��� ���͸� �����Ѵ�. 
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
		MsgAssert("nullptr ���͸� Start�Ϸ��� �߽��ϴ�.");
		return;
	}

	// ������ ������ Level = this
	_Actor->SetOwner(this);
	_Actor->SetOrder(_Order);
	_Actor->Start();
}

// ���;�����Ʈ
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	{
		// Ű�� : int , ������ : GameEngineActor* �� �����ϴ� ����Ʈ
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		// ���۳�尡 ����尡 �ƴҶ� ���� ++�Ͽ� ��ȸ 
		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			// ����������  
			// ����� ������Ÿ�� : �ڷᱸ���̸�
			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				// ���Ͱ� ������� ���ĺ��� ȭ�鿡 ����ִ� �ð��� ����Ѵ�. 
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

// ���ͷ���
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

// ������ ������ ȣ���Ͽ� ����Ʈ�� �߰��ϴ� �Լ�
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("nullptr�� ������ ������ �׷�ӿ� �������� �߽��ϴ�.");
	}

	// ���� �̹� ���������� �ִ�.
	// map �� ���� 
	// �����Ͱ� �������� �ʴ´ٸ� �߰��Ѵ�.
	// �����Ͱ� �̹� �ִٸ�, �׳༮�� ��ȯ�Ѵ�. 
	Renders[_Render->GetOrder()].push_back(_Render);
}