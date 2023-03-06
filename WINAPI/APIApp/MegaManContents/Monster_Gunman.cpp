#include "Monster_GunMan.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

float Monster_GunMan::Time = 0.0f;

void Monster_GunMan::ChangeState(GunmanState _State)
{
	// 인자값으로 다음상태를 설정
	m_NextState = _State;
	// 이전상태는 현재상태
	m_PrevState = m_CurState;
	// 현재 상태는 다음상태
	m_CurState = m_NextState;
	
	switch (m_NextState)
	{
	case GunmanState::NONE:
		break;
	case GunmanState::IDLE:
		break;
	case GunmanState::MOVE:
		break;
	case GunmanState::SHOT:
		break;
	default:
		break;
	}
	
	switch (m_PrevState)
	{
	case GunmanState::NONE:
		break;
	case GunmanState::IDLE:
		break;
	case GunmanState::MOVE:
		break;
	case GunmanState::SHOT:
		break;
	default:
		break;
	}
}




Monster_GunMan::Monster_GunMan() :
	m_Render(nullptr)
{
}

Monster_GunMan::~Monster_GunMan()
{
}

void Monster_GunMan::Start()
{
	
	m_Dir = float4::Left;

	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	m_Render = CreateRender(ZORDER::MONSTER);
	// 렌더링시 x축 y축의 크기설정
	m_Render->SetScale({ 320 * 4.0f , 240 * 4.2f });

	// 충돌체생성 , 그룹지정
	m_Collider = CreateCollision(COLORDER::MONSTER);
	m_Collider->SetScale({ 150 , 150 });
	m_Collider->SetPosition({ 0, -100 });

	m_Render->CreateAnimation({ .AnimationName = "Gunman_idle_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Shot_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Move_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.08f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_throw_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_Render->CreateAnimation({ .AnimationName = "Gunman_idle_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Shot_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Move_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.1f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_throw_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_Render->ChangeAnimation("Gunman_idle_Left");
	
}

void Monster_GunMan::Update(float _DeltaTime)
{
	// 단일 충돌체크 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// 여기서 이펙트 같은거를 출력
		this->Death();
	}
	

	/* 충돌시 코드 참고용
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Player) }))
	{
		int a = 0;
	}

	std::vector<GameEngineCollision*> Collision;
	if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Player) }, Collision))
	{
		for (size_t i = 0; i < Collision.size(); i++)
		{
			 Monster* FindMonster = Collision[i]->GetOwner<Monster>();

			GameEngineActor* ColActor = Collision[i]->GetActor();


			int a = 0;
		}
	}*/
}

void Monster_GunMan::Render(float _DeltaTime)
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

	// m_Collider->DebugRender();
}
