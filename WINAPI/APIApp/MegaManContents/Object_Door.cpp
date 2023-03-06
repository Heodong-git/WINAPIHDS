#include "Object_Door.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

Object_Door::Object_Door()
{
}

Object_Door::~Object_Door()
{
}

void Object_Door::Start()
{
	// �ִϸ��̼� ���� ����
	m_AnimationRender = CreateRender(ZORDER::OBJECT);
	m_AnimationRender->SetScale(float4{ 800, 840 });

	// ���⼭ �ִϸ��̼� ����� �ϴ� 
	// �� ���⼭���� �ٽ� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "close_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 0 , .InterTime = 1.0f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "open_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 12 , .InterTime = 0.08f , .Loop = false });

	m_AnimationRender->ChangeAnimation("close_door");
	
	// �浹ü ����
	m_Collider = CreateCollision(COLORDER::OBJECT_DOOR);
}

void Object_Door::Update(float _DeltaTime)
{
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER),  .TargetColType = CT_Rect , .ThisColType = CT_Rect}))
	{
		// ���⼭ �÷��̾�� �浹���� ��, �ִϸ��̼��� ���� ������ �ִϸ��̼����� �ٲ�����
		// �ϴ� �ִϸ��̼Ǻ��� ����
		m_AnimationRender->ChangeAnimation("open_door");
		return;
	}
}

void Object_Door::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
