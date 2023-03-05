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
	m_AnimationRender->SetScale(float4{ 500, 500 });

	// ���⼭ �ִϸ��̼� ����� �ϴ� 
	// �� ���⼭���� �ٽ� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "wait_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 0 , .InterTime = 1.0f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "open_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 12 , .InterTime = 0.8f });

	m_AnimationRender->ChangeAnimation("wait_door");
	
	// �浹ü ����
	m_Collider = CreateCollision(COLORDER::OBJECT_DOOR);
	m_Collider->SetScale({ 100, 100 });
	m_Collider->SetPosition({ 0, 0 });
	
}

void Object_Door::Update(float _DeltaTime)
{
	if (false == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) }))
	{
		int a = 0;
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
