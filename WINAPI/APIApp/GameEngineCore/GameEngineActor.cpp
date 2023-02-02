#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor()
{
}

// �ڽ��� �����Ҵ��� �޸𸮵��� �ڽ��� �Ҹ��ڿ��� �����Ѵ�. 
GameEngineActor::~GameEngineActor()
{
	// ranged for �������
	// ����������Ʈ�� ��ȸ�ϸ� �����Ҵ�� �޸𸮸� ����
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}

	// �浹ü����Ʈ�� ��ȸ�ϸ� �����Ҵ�� �޸� ����
	for (GameEngineCollision* _Collision : CollisionList)
	{
		if (nullptr == _Collision)
		{
			continue;
		}

		delete _Collision;
		_Collision = nullptr;
	}
}

// �� �ڽ��� ������ ������ ��ȯ
GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

// ��������
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	// �����ε��� �Լ��� ȣ��
	GameEngineRender* Render = CreateRender(_Order);
	// �������� ����� �̹��� ����
	Render->SetImage(_Image);

	// ������ ���� ��ü�� �ּҰ� ��ȯ
	return Render;
}

// ��������
GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{	
	// ������ �����Ҵ�
	GameEngineRender* Render = new GameEngineRender();

	// ������ �θ�, ���������� ����
	// ���Ͱ� ������ ������ ����Ʈ�� �߰�
	Render->SetOwner(this);
	Render->SetOrder(_Order);
	RenderList.push_back(Render);

	// ������ ������ ��ü�� �ּҰ� ��ȯ
	return Render;
}

// �浹ü �����Լ�
GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	// �浹ü Ŭ���� �����Ҵ�
	GameEngineCollision* Collision = new GameEngineCollision();

	// ���� ���� , Collision �׷찪 ���� , ����Ʈ�� �߰�
	Collision->SetOwner(this);
	// ���ڷ� ���� �׷� ���� �־��ش�.
	Collision->SetOrder(_GroupIndex);
	CollisionList.push_back(Collision);
	
	// ������ �浹ü ��ȯ 
	return Collision;
}

void GameEngineActor::Release()
{
	{
		std::list<GameEngineRender*>::iterator StartIter = RenderList.begin();
		std::list<GameEngineRender*>::iterator EndIter = RenderList.end();

		// ��������Ʈ ��ȸ
		for (; StartIter != EndIter; )
		{
			GameEngineRender* ReleaseRender = *StartIter;

			if (nullptr == ReleaseRender)
			{
				MsgAssert("nullptr �� ������ ���ο� ����ֽ��ϴ�.");
			}

			// ������ �������°� �ƴ϶�� ������ �ʰ� ���� ���� �̵� �� ���ǹ�����. 
			if (false == ReleaseRender->IsDeath())
			{
				++StartIter;
				continue;
			}

			// �ڵ尡 �����Դٸ� ���������̱� ������ ����Ʈ���� �����ش�. 
			StartIter = RenderList.erase(StartIter);

			// ������ �༮�� �ּҰ��� �˰� �ֱ� ������ �޸𸮿��� ���� �� nullptr �ʱ�ȭ
			delete ReleaseRender;
			ReleaseRender = nullptr;
		}
	}
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineCollision* ReleaseCollision = *StartIter;

			if (nullptr == ReleaseCollision)
			{
				MsgAssert("nullptr �� ������ ���ο� ����ֽ��ϴ�.");
			}

			if (false == ReleaseCollision->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = CollisionList.erase(StartIter);

			delete ReleaseCollision;
			ReleaseCollision = nullptr;
		}
	}
}