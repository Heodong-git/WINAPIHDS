#include "Monster_GunMan.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Effect_Explosion.h"
#include "Effect_Hit.h"
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
	
	// 다음 상태
	switch (m_NextState)
	{
	case GunmanState::IDLE:
		Idle_Start();
		break;
	case GunmanState::SHOT:
		Shot_Start();
		break;
	}

	switch (m_PrevState)
	{
	case GunmanState::IDLE:
		Idle_End();
		break;
	case GunmanState::SHOT:
		Shot_End();
		break;
	}
}

void Monster_GunMan::UpdateState(float _DeltaTime)
{
	switch (m_CurState)
	{
	case GunmanState::IDLE:
		Idle_Update(_DeltaTime);
		break;
	case GunmanState::SHOT:
		Shot_Update(_DeltaTime);
		break;
	}
}

void Monster_GunMan::Idle_Start()
{
	AnimDirCheck("Gunman_Idle");
}

void Monster_GunMan::Idle_Update(float _DeltaTime)
{
}

void Monster_GunMan::Idle_End()
{
}

void Monster_GunMan::Shot_Start()
{
}

void Monster_GunMan::Shot_Update(float _DeltaTime)
{
}

void Monster_GunMan::Shot_End()
{
}

Monster_GunMan::Monster_GunMan()
{
}

Monster_GunMan::~Monster_GunMan()
{
}

void Monster_GunMan::Start()
{
	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	m_AnimationRender = CreateRender(ZORDER::MONSTER);
	// 렌더링시 x축 y축의 크기설정
	m_AnimationRender->SetScale({ 320 * 4.0f , 240 * 4.2f });

	// 충돌체생성 , 그룹지정
	m_Collider = CreateCollision(COLORDER::MONSTER);
	m_Collider->SetScale({ 150 , 150 });
	m_Collider->SetPosition({ 0, -100 });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_idle" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_Shot" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_Move" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.08f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_throw" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_idle" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_Shot" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_Move" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.1f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_throw" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	ChangeState(GunmanState::IDLE);
}

void Monster_GunMan::AnimDirCheck(const std::string_view& _AnimationName)
{
	// 현재 방향문자열 값을 받아온다. 
	std::string PrevDirString = m_DirString;
	// 해당하는 방향의 애니메이션으로 change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());

	// 플레이어의 위치가 나보다 왼쪽에 있다면 ~ 오른쪽에 있다면 ~ 코드 작성해야함 
	
	
	// 변경 이후 
	// 만약 이전 방향문자열이 현재 방향문자열과 다르다면
	if (PrevDirString != m_DirString)
	{
		m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	}
}


void Monster_GunMan::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);

	// 단일 충돌체크 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// 여기서 이펙트 같은거를 출력
		Effect_Hit* Hit_Effect = GetLevel()->CreateActor<Effect_Hit>();
		Hit_Effect->SetPos(GetPos() + float4 { -30, - 100});

		this->Death();
		
		Effect_Explosion* E_Effect = GetLevel()->CreateActor<Effect_Explosion>();
		E_Effect->SetPos(GetPos());

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
