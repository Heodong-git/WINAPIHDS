#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	// ��������Ʈ�� ��ȸ�Ͽ� ����Ǿ��ִ� �����Ҵ�� �޸𸮸� ��� ����
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}
}

GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}


// ���ڷ� �־��� �̹���, Order ������ ����Ŭ��������
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	// �����ε��� �Լ��� ȣ��
	GameEngineRender* Render = CreateRender(_Order);
	// �������� ����� �̹��� ����
	Render->SetImage(_Image);

	// �۾� �Ϸ�� ��ü ��ȯ
	return Render;
}


GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{	
	// ������ �����Ҵ�
	GameEngineRender* Render = new GameEngineRender();

	// �����ൿ������ �ӽ÷� �ϴ� �Ѵ� ���� 
	Render->SetOwner(this);
	// Renderer ���� = this ( ���Լ��� ȣ���� ��ü�� �ּ� ) 
	Render->Owner = this;
	// Zorder �� ����
	Render->SetOrder(_Order);
	// ���Ͱ� ������ ����Ʈ�� �־��ش�. 
	RenderList.push_back(Render);

	// �۾��Ϸ�� ������ ��ȯ
	return Render;
}

// �浹ü �����Լ�
GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	// �浹ü Ŭ���� �����Ҵ�
	GameEngineCollision* Collision = new GameEngineCollision();

	// ������ �浹ü�� ���ʴ� �Լ��� ȣ���� ��ü�� �ȴ�.
	Collision->SetOwner(this);
	// ���ڷ� ���� �׷� ���� �־��ش�.
	Collision->SetOrder(_GroupIndex);
	// ���Ͱ� ������ �浹ü ����Ʈ�� �־��ش�.
	CollisionList.push_back(Collision);
	
	// ������ �浹ü ��ȯ 
	return Collision;
}