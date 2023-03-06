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
	// 애니메이션 렌더 생성
	m_AnimationRender = CreateRender(ZORDER::OBJECT);
	m_AnimationRender->SetScale(float4{ 800, 840 });

	// 여기서 애니메이션 만들고 일단 
	// 문 여기서부터 다시 
	m_AnimationRender->CreateAnimation({ .AnimationName = "close_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 0 , .InterTime = 1.0f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "open_door" , .ImageName = "object_boss_door.bmp",
									   .Start = 0 , .End = 12 , .InterTime = 0.08f , .Loop = false });

	m_AnimationRender->ChangeAnimation("close_door");
	
	// 충돌체 생성
	m_Collider = CreateCollision(COLORDER::OBJECT_DOOR);
}

void Object_Door::Update(float _DeltaTime)
{
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER),  .TargetColType = CT_Rect , .ThisColType = CT_Rect}))
	{
		// 여기서 플레이어랑 충돌했을 때, 애니메이션이 문이 열리는 애니메이션으로 바뀌어야함
		// 일단 애니메이션부터 변경
		m_AnimationRender->ChangeAnimation("open_door");
		return;
	}
}

void Object_Door::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
