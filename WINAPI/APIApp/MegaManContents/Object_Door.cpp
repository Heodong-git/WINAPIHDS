#include "Object_Door.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpacePortLevel.h"
#include "Player_Zero.h"
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
	// 플레이어와 충돌이 시작되었을때 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER),  .TargetColType = CT_Rect , .ThisColType = CT_Rect}))
	{
		// 내 애니메이션을 변경하고
		m_AnimationRender->ChangeAnimation("open_door");
		// 레벨을 받아와서
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// 예외처리하고
		if (nullptr != Level)
		{
			// 플레이어 상태가 DOORCONTACT 상태가 아니라면
			if (false == (STATEVALUE::DOOR_CONTACT == Level->GetPlayer()->GetState()))
			{
				// 플레이어의 상태를 DOORCONTACT 상태로 변경한다. 
				Level->GetPlayer()->ChangeState(STATEVALUE::DOOR_CONTACT);
				return;
			}
		}
	}

	else
	{
		m_AnimationRender->ChangeAnimation("close_door");
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
