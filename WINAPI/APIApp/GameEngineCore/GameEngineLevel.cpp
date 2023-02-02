#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

#include <GameEngineBase/GameEngineDebug.h>	
#include <GameEnginePlatform/GameEngineWindow.h>

bool GameEngineLevel::IsDebugRender = false;
float4 GameEngineLevel::TextOutStart = float4::Zero;
std::vector<std::string> GameEngineLevel::DebugTexts;

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

// ���콺 ��ǥ�� �޾ƿ���. 
float4 GameEngineLevel::GetMousePos()
{
	return GameEngineWindow::GetMousePosition();
}
float4 GameEngineLevel::GetMousePosToCamera()
{
	return GameEngineWindow::GetMousePosition() + CameraPos;
}

void GameEngineLevel::Release()
{
	{ // �ݸ��� ����
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
			std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

			for (; CollisionIterStart != CollisionIterEnd; )
			{
				GameEngineCollision* ReleaseCollision = *CollisionIterStart;

				// Actors.erase()
				if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
				{
					++CollisionIterStart;
					continue;
				}

				CollisionIterStart = CollisionList.erase(CollisionIterStart);
			}
		}
	}

	{ // �������� ����
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			std::list<GameEngineRender*>::iterator RenderIterStart = RenderList.begin();
			std::list<GameEngineRender*>::iterator RenderIterEnd = RenderList.end();

			for (; RenderIterStart != RenderIterEnd; )
			{
				GameEngineRender* ReleaseRender = *RenderIterStart;

				// Actors.erase()
				if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
				{
					++RenderIterStart;
					continue;
				}

				RenderIterStart = RenderList.erase(RenderIterStart);
			}
		}
	}

	{ // ���͸� ����

		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			std::list<GameEngineActor*>::iterator ActorIterStart = ActorList.begin();
			std::list<GameEngineActor*>::iterator ActorIterEnd = ActorList.end();

			for (; ActorIterStart != ActorIterEnd; )
			{
				GameEngineActor* ReleaseActor = *ActorIterStart;

				// Actors.erase()
				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					ReleaseActor->Release();
					++ActorIterStart;
					continue;
				}

				ActorIterStart = ActorList.erase(ActorIterStart);

				delete ReleaseActor;
				ReleaseActor = nullptr;
			}
		}
	}
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
				if (nullptr == Renderer || false == Renderer->IsUpdate())
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
	// CollisionDebugRender
	{ // �ݸ��� ����
		if (true == IsDebugRender)
		{
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

			for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
			{
				std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;
				std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
				std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

				for (; CollisionIterStart != CollisionIterEnd; ++CollisionIterStart)
				{
					GameEngineCollision* DebugCollision = *CollisionIterStart;
					if (nullptr == DebugCollision || false == DebugCollision->IsUpdate())
					{
						continue;
					}
					DebugCollision->DebugRender();
				}
			}
		}
	}

	// �����е��� text ���
	{
		TextOutStart = float4::Zero;

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
			TextOutA(ImageDc, TextOutStart.ix(), TextOutStart.iy(), DebugTexts[i].c_str(), DebugTexts[i].size());
			TextOutStart.y += 20.0f;
		}

		DebugTexts.clear();
	}
}

// ������ ������ ȣ���Ͽ� �ʿ� �߰��ϴ� �Լ�
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

// �浹ü ���� �� ȣ���Ͽ� �ʿ� �߰��ϴ� �Լ� 
void GameEngineLevel::PushCollision(GameEngineCollision* _Collision)
{
	// ����ó��
	if (nullptr == _Collision)
	{
		MsgAssert("nullptr�� �浹ü�� �浹 �׷�ӿ� �������� �߽��ϴ�.");
	}

	// �̹� �ִٸ� �׳༮�� ��ȯ, ���ٸ� �߰��ϴ� map �� ���� 
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}