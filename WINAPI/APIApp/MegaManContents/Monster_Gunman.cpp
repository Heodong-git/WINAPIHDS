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
	// ���ڰ����� �������¸� ����
	m_NextState = _State;
	// �������´� �������
	m_PrevState = m_CurState;
	// ���� ���´� ��������
	m_CurState = m_NextState;
	
	switch (m_NextState)
	{
	case GunmanState::IDLE:
		break;
	case GunmanState::SHOT:
		break;
	default:
		break;
	}
	
	switch (m_PrevState)
	{
	case GunmanState::IDLE:
		break;
	case GunmanState::SHOT:
		break;
	default:
		break;
	}
}

Monster_GunMan::Monster_GunMan()
{
}

Monster_GunMan::~Monster_GunMan()
{
}

void Monster_GunMan::Start()
{
	// �������� , ������ ����� �̹���, Zorder �� �Է�
	m_Render = CreateRender(ZORDER::MONSTER);
	// �������� x�� y���� ũ�⼳��
	m_Render->SetScale({ 320 * 4.0f , 240 * 4.2f });

	// �浹ü���� , �׷�����
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
	// ���� �浹üũ 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// ���⼭ ����Ʈ �����Ÿ� ���
		Effect_Hit* Hit_Effect = GetLevel()->CreateActor<Effect_Hit>();
		Hit_Effect->SetPos(GetPos() + float4 { -30, - 100});

		this->Death();
		
		Effect_Explosion* E_Effect = GetLevel()->CreateActor<Effect_Explosion>();
		E_Effect->SetPos(GetPos());

	}
	

	/* �浹�� �ڵ� �����
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
	// ������
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
