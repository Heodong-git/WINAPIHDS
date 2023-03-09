#include "Monster_GunMan.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SpacePortLevel.h"
#include "Player_Zero.h"
#include "Effect_Explosion.h"
#include "Effect_Hit.h"
#include "Object_Bullet.h"
#include "ContentsEnum.h"

void Monster_GunMan::ChangeState(GunmanState _State)
{
	// ���ڰ����� �������¸� ����
	m_NextState = _State;
	// �������´� �������
	m_PrevState = m_CurState;
	// ���� ���´� ��������
	m_CurState = m_NextState;
	
	// ���� ����
	switch (m_NextState)
	{
	case GunmanState::IDLE:
		Idle_Start();
		break;
	case GunmanState::SHOT:
		Shot_Start();
		break;
	case GunmanState::MOVE:
		Move_Start();
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
	case GunmanState::MOVE:
		Move_End();
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
	case GunmanState::MOVE:
		Move_Update(_DeltaTime);
		break;
	}
}

void Monster_GunMan::Idle_Start()
{
	AnimDirCheck("Gunman_Idle");
}

void Monster_GunMan::Idle_Update(float _DeltaTime)
{
	// �׳� ���⼭ ��Ÿ���� ���ҽ�Ű��, 0�� �ƴٸ� �Ʒ��ڵ嵿���ϴ°ɷ� 
	m_ShotCooldown += _DeltaTime;
	
	if (m_ShotMaxCooldown <= m_ShotCooldown)
	{
		// ������ �޾ƿ��� ��... 
		m_ShotCooldown = 0.0f;
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
		if (nullptr != Level)
		{
			float4 PlayerPos = Level->GetPlayer()->GetPos();
			float Range = GetPos().x - PlayerPos.x;
			float absRange = abs(Range);

			if (absRange <= m_ShotRange)
			{
				ChangeState(GunmanState::SHOT);
				return;
			}
		}
	}

	AnimDirCheck("Gunman_Idle");
}

void Monster_GunMan::Idle_End()
{
}

void Monster_GunMan::Shot_Start()
{
	AnimDirCheck("Gunman_shot");

	// ó���ѹ��� ��ġ�� 
	const char* Dir = GetDirString().c_str();
	if (0 == strcmp(Dir, "Right_"))
	{
		Object_Bullet* NewBullet = GetLevel()->CreateActor<Object_Bullet>();
		NewBullet->SetMoveDir(float4::Right);
		NewBullet->SetPos(GetPos() + float4{ 130, -160 });
	}

	else if (0 == strcmp(Dir, "Left_"))
	{
		Object_Bullet* NewBullet = GetLevel()->CreateActor<Object_Bullet>();
		NewBullet->SetMoveDir(float4::Left);
		NewBullet->SetPos(GetPos() + float4{ -130, -160 });
	}

}

void Monster_GunMan::Shot_Update(float _DeltaTime)
{
	
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(GunmanState::IDLE);
		return;
	}
}

void Monster_GunMan::Shot_End()
{
}

void Monster_GunMan::Move_Start()
{
	AnimDirCheck("gunman_Move");
}

void Monster_GunMan::Move_Update(float _DeltaTime)
{
	m_MoveTime += _DeltaTime;
	if (3 >= m_MoveTime)
	{
		m_AnimationRender->ChangeAnimation("Left_gunman_move");
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
	}

	else if (3 < m_MoveTime)
	{
		m_AnimationRender->ChangeAnimation("right_gunman_move");
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
	}

	if (6 <= m_MoveTime)
	{
		m_MoveTime -= m_MoveTime;
	}
}

void Monster_GunMan::Move_End()
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
	// �������� , ������ ����� �̹���, Zorder �� �Է�
	m_AnimationRender = CreateRender(ZORDER::MONSTER);
	// �������� x�� y���� ũ�⼳��
	m_AnimationRender->SetScale({ 320 * 4.0f , 240 * 4.2f });

	// �浹ü���� , �׷�����
	m_Collider = CreateCollision(COLORDER::MONSTER);
	m_Collider->SetScale({ 150 , 150 });
	m_Collider->SetPosition({ 0, -100 });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_idle" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_Shot" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.08f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_Move" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.06f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Gunman_throw" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_idle" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_Shot" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_Move" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.06f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Gunman_throw" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	ChangeState(GunmanState::IDLE);
}

void Monster_GunMan::AnimDirCheck(const std::string_view& _AnimationName)
{
	// ���� ���⹮�ڿ� ���� �޾ƿ´�. 
	std::string PrevDirString = m_DirString;
	// �ش��ϴ� ������ �ִϸ��̼����� change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());

	// �÷��̾��� ��ġ�� ������ ���ʿ� �ִٸ� ~ �����ʿ� �ִٸ� ~ �ڵ� �ۼ��ؾ��� 
	SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
	if (nullptr != Level)
	{
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float Range = GetPos().x - PlayerPos.x;
		if (0 <= Range)
		{
			m_DirString = "Left_";
		}

		else if (0 > Range)
		{
			m_DirString = "Right_";
		}
	}
	
	// ���� ���� 
	// ���� ���� ���⹮�ڿ��� ���� ���⹮�ڿ��� �ٸ��ٸ�
	if (PrevDirString != m_DirString)
	{
		m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	}
}


void Monster_GunMan::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);

	// ���� �浹üũ 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// ���⼭ ����Ʈ �����Ÿ� ���
		Effect_Hit* Hit_Effect = GetLevel()->CreateActor<Effect_Hit>();
		Hit_Effect->SetPos(GetPos() + float4 { -30, - 100});

		this->Death();
		
		m_Sound = GameEngineResources::GetInst().SoundPlayToControl("fire.wav");
		m_Sound.LoopCount(1);
		m_Sound.Volume(0.2f);

		Effect_Explosion* E_Effect = GetLevel()->CreateActor<Effect_Explosion>();
		E_Effect->SetPos(GetPos());

	}
	
	// �浹�� �ڵ� �����
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) }))
	{
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
		if (nullptr != Level)
		{
			Player_Zero* Player = Level->GetPlayer();
			float4 PlayerPos = Player->GetPos();
			float Range = GetPos().x - PlayerPos.x;

			if (Range >0.0f)
			{
				Player->SetMove(float4::Left * 100.0f);
				Player->ChangeState(STATEVALUE::HIT);
				GetLevel()->SetCameraMove(float4::Left * 100.0f);
				return;
			}

			else if (Range <= 0.0f)
			{
				Player->SetMove(float4::Right * 100.0f);
				Player->ChangeState(STATEVALUE::HIT);
				GetLevel()->SetCameraMove(float4::Right * 100.0f);
				return;
			}
		}
	}

	/*std::vector<GameEngineCollision*> Collision;
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
	//// ������
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);
}
