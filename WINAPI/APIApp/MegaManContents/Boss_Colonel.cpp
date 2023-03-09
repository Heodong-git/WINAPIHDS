#include "Boss_Colonel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <time.h>
#include "SpacePortLevel.h"
#include "Effect_Hit.h"
#include "Effect_Boss_Hit.h"
#include "Effect_Explosion.h"
#include "Effect_Lightning.h"
#include "Player_Zero.h"
#include "UI_PlayerHpBar.h"
#include "ContentsEnum.h"

Boss_Colonel::Boss_Colonel()
{
}

Boss_Colonel::~Boss_Colonel()
{
}

void Boss_Colonel::Start()
{
	m_AnimationRender = CreateRender(ZORDER::BOSS);
	m_AnimationRender->SetScale({ 640 * 1.7f , 480 * 2.0f });
	AnimationCreate();
	m_AnimationRender->ChangeAnimation("Left_Colonel_Start");

	ChangeState(BOSSSTATE::START);
	// ����ٽ� 
	m_Collider = CreateCollision(COLORDER::BOSS);
	m_Collider->SetScale(float4{ 200, 200 });
	m_Collider->SetPosition({ 0, -100 });
	
	m_AttackCollider = CreateCollision(COLORDER::BOSSATTACK);
	m_AttackCollider->SetScale(float4{ 250, 250 });
	m_AttackCollider->Off();
}

void Boss_Colonel::Update(float _DeltaTime)
{

	// ���⼭ �÷��̾ fight ���°� �ƴ϶�� ������Ʈ �������� return 
	if (true == m_Invincibility)
	{
		if (m_InvincibilityTime >= m_MaxInvincibility)
		{
			m_InvincibilityTime = 0.0f;
			m_Invincibility = false;
		}

		m_InvincibilityTime += _DeltaTime;
	}

	// ���� �浹üũ 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// ������ �ƴҶ��� 
		if (false == m_Invincibility)
		{
			// �������·� ����
			m_Invincibility = true;
			SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		
			if (nullptr != Level)
			{
				// �÷��̾��� x ����ġ�� 
				float4 PlayerPos = Level->GetPlayer()->GetPos();
				float Range = GetPos().x - PlayerPos.x;

				/*m_Sound = GameEngineResources::GetInst().SoundPlayToControl("hit_sound.wav");
				m_Sound.LoopCount(1);
				m_Sound.Volume(0.2f);*/

				if (0 <= Range)
				{
					

					Effect_Boss_Hit* Effect = GetLevel()->CreateActor<Effect_Boss_Hit>();
					Effect->SetPos(GetPos() + float4{ -70, -150 });
					Effect->GetEffectRender()->ChangeAnimation("right_blade_hit_effect");

					Damage(1);
					return;
				}

				else if (0 > Range)
				{
					Effect_Boss_Hit* Effect = GetLevel()->CreateActor<Effect_Boss_Hit>();
					Effect->SetPos(GetPos() + float4{ 70, -150 });
					Effect->GetEffectRender()->ChangeAnimation("left_blade_hit_effect");
					Damage(1);
					return;
				}
			}
		}
	}

	if (true == IsHpZero())
	{
		ChangeState(BOSSSTATE::DEATH);
	}

	UpdateState(_DeltaTime);
}

void Boss_Colonel::Render(float _DeltaTime)
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

void Boss_Colonel::AnimDirCheck(const std::string_view& _AnimationName)
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
		// �÷��̾� ��ġ�� �޾ƿԾ�
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float Range = GetPos().x - PlayerPos.x;
		if (0 < Range)
		{
			m_DirString = "Left_";
		}

		else
		{
			m_DirString = "Right_";
		}
	}

}

void Boss_Colonel::ChangeState(BOSSSTATE _State)
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
	case BOSSSTATE::START:
		Start_Start();
		break;
	case BOSSSTATE::IDLE:
		Idle_Start();
		break;
	case BOSSSTATE::TELEPORT:
		Teleport_Start();
		break;
	case BOSSSTATE::FIRST_ATTACK:
		First_Attack_Start();
		break;
	case BOSSSTATE::SECOND_ATTACK:
		Second_Attack_Start();
		break;
	case BOSSSTATE::LIGHTNING_PATTERN:
		First_Pattern_Start();
		break;
	case BOSSSTATE::DEATH:
		Death_Start();
		break;
	}

	switch (m_PrevState)
	{
	case BOSSSTATE::START:
		Start_End();
		break;
	case BOSSSTATE::IDLE:
		Idle_End();
		break;
	case BOSSSTATE::TELEPORT:
		Teleport_End();
		break;
	case BOSSSTATE::FIRST_ATTACK:
		First_Attack_End();
		break;
	case BOSSSTATE::SECOND_ATTACK:
		Second_Attack_End();
		break;
	case BOSSSTATE::LIGHTNING_PATTERN:
		First_Pattern_End();
		break;
	case BOSSSTATE::DEATH:
		Death_End();
	}
}

void Boss_Colonel::UpdateState(float _DeltaTime)
{
	switch (m_CurState)
	{
	case BOSSSTATE::START:
		Start_Update(_DeltaTime);
		break;
	case BOSSSTATE::IDLE:
		Idle_Update(_DeltaTime);
		break;
	case BOSSSTATE::TELEPORT:
		Teleport_Update(_DeltaTime);
		break;
	case BOSSSTATE::FIRST_ATTACK:
		First_Attack_Update(_DeltaTime);
		break;
	case BOSSSTATE::SECOND_ATTACK:
		Second_Attack_Update(_DeltaTime);
		break;
	case BOSSSTATE::LIGHTNING_PATTERN:
		First_Pattern_Update(_DeltaTime);
		break;
	case BOSSSTATE::DEATH:
		Death_Update(_DeltaTime);
		break;
	}
}

void Boss_Colonel::AnimationCreate()
{
	// �������۸��
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Start" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });
	// �⺻�ڼ� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_idle" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 2 , .End = 4 , .InterTime = 0.2f });
	// �ڷ���Ʈ left 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Teleport" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 5 , .End = 8 , .InterTime = 0.14f , .Loop = false });
	// ��Ÿ 1Ÿ
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_first_attack" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 9 , .End = 13 , .InterTime = 0.08f });

	// ��Ÿ 2Ÿ
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_second_attack" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 14 , .End = 19 , .InterTime = 0.08f });

	// ���� ����
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_lightning" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 21 , .End = 38 , .InterTime = 0.08f });

	// ���� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Death" , .ImageName = "spaceport_colonel_left.bmp" ,
							.Start = 45 , .End = 45 , .InterTime = 0.08f , .Loop = false });


	// ������ -----------------------------------------

	// �������۸��
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Colonel_Start" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });

	// �⺻�ڼ� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_idle" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 2 , .End = 4 , .InterTime = 0.2f });

	// �ڷ���Ʈ right 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_Teleport" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 5 , .End = 8, .InterTime = 0.14f , .Loop = false });

	// ����1Ÿ 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_first_attack" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 9 , .End = 13, .InterTime = 0.08f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_second_attack" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 14 , .End = 19, .InterTime = 0.08f , .Loop = false });

	// ���� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_Death" , .ImageName = "spaceport_colonel_right.bmp" ,
							.Start = 45 , .End = 45 , .InterTime = 0.08f , .Loop = false });

	// ���������� �ִϸ��̼�
	m_AnimationRender->CreateAnimation({ .AnimationName = "colonel_delay" , .ImageName = "spaceport_colonel_right.bmp" ,
							.Start = 46 , .End = 47 , .InterTime = 0.5f , .Loop = false });
}

void Boss_Colonel::Start_Start()
{
	AnimDirCheck("colonel_start");
}

void Boss_Colonel::Start_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(BOSSSTATE::IDLE);
		return;
	}
}

void Boss_Colonel::Start_End()
{
}

void Boss_Colonel::Idle_Start()
{
	AnimDirCheck("Colonel_idle");
}

void Boss_Colonel::Idle_Update(float _DeltaTime)
{
	AnimDirCheck("Colonel_idle");


	if (true == m_SkillUse)
	{
		m_SkillCoolDown -= _DeltaTime;

		if (m_SkillCoolDown <= 0.0f)
		{
			m_SkillCoolDown = m_SkillCoolDownMax;
			m_SkillUse = false;
		}
	}


	// ���⼭ ��ŸƮ ����� ������ Hp�ٸ� ���̰��� 
	if (nullptr != m_HpBar && false == m_HpBar->GetBossHpRender()->IsUpdate())
	{
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		if (nullptr != Level)
		{
			if (true == Level->GetPlayer()->IsBossFight())
			{
				m_HpBar->GetBossHpRender()->On();
			}

		}
	}

	if (false == m_HpBar->GetBossHpRender()->IsUpdate())
	{
		return;
	}

	int RandomValue = GameEngineRandom::MainRandom.RandomInt(static_cast<int>(BOSSSTATE::TELEPORT), static_cast<int>(BOSSSTATE::LIGHTNING_PATTERN));
	switch (static_cast<BOSSSTATE>(RandomValue))
	{
	
	case BOSSSTATE::TELEPORT:
	{
		if (false == m_SkillUse)
		{
			m_SkillUse = true;
			ChangeState(BOSSSTATE::TELEPORT);
			return;
		}
	}
		break;
	case BOSSSTATE::LIGHTNING_PATTERN:
	{
		if (false == m_SkillUse)
		{
			m_SkillUse = true;
			ChangeState(BOSSSTATE::LIGHTNING_PATTERN);
			return;
		}
	}
		break;
	}
	
}

void Boss_Colonel::Idle_End()
{
}

void Boss_Colonel::Teleport_Start()
{
	AnimDirCheck("colonel_teleport");
	m_Sound = GameEngineResources::GetInst().SoundPlayToControl("teleport.wav");
	m_Sound.LoopCount(1);
	m_Sound.Volume(0.2f);
}

void Boss_Colonel::Teleport_Update(float _DeltaTime)
{
	
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// �����̵� �ִϸ��̼��� ������ �÷��̾��� ��, Ȥ�� �ڷ� �̵��ؼ� ����
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
		if (nullptr != Level)
		{
			float4 PlayerPos = Level->GetPlayer()->GetPos();
			float PlayerPosX = PlayerPos.x;

			int RandomValue = GameEngineRandom::MainRandom.RandomInt(1, 2);
			
			if (1 == RandomValue)
			{
				float4 MovePos = PlayerPos + float4{ 150, 0 };
				SetPos({ MovePos.x , GetPos().y });
			}

			else if (2 == RandomValue)
			{
				float4 MovePos = PlayerPos + float4{ -150, 0 };
				SetPos({ MovePos.x , GetPos().y });
			}
			
		}

		ChangeState(BOSSSTATE::FIRST_ATTACK);
		return;
	}
}

void Boss_Colonel::Teleport_End()
{
}

void Boss_Colonel::First_Attack_Start()
{
	AnimDirCheck("colonel_first_attack");
	
}

void Boss_Colonel::First_Attack_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(BOSSSTATE::SECOND_ATTACK);
		return;
	}

	AnimDirCheck("colonel_first_attack");
	// ���⼭�� �÷��̾�ó�� �浹ü �������� 

	// �÷��̾��� ��ġ�� ������ ���ʿ� �ִٸ� ~ �����ʿ� �ִٸ� ~ �ڵ� �ۼ��ؾ��� 
	SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
	// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
	if (nullptr != Level)
	{
		// �÷��̾� ��ġ�� �޾ƿԾ�
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float Range = GetPos().x - PlayerPos.x;
		if (0 < Range)
		{
			m_AttackCollider->SetPosition(float4{ -150, -100 });
		}

		else
		{
			m_AttackCollider->SetPosition(float4{ 150, -100 });
		}
	}
}

void Boss_Colonel::First_Attack_End()
{
	m_AttackCollider->Off();
}

void Boss_Colonel::Second_Attack_Start()
{
	AnimDirCheck("colonel_second_attack");
}

void Boss_Colonel::Second_Attack_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(BOSSSTATE::IDLE);
		return;
	}

	AnimDirCheck("colonel_second_attack");
	SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
	// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
	if (nullptr != Level)
	{
		// �÷��̾� ��ġ�� �޾ƿԾ�
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float Range = GetPos().x - PlayerPos.x;
		if (0 < Range)
		{
			m_AttackCollider->SetPosition(float4{ -150, -100 });
			m_AttackCollider->On();
		}

		else
		{
			m_AttackCollider->SetPosition(float4{ 150, -100 });
			m_AttackCollider->On();
		}
	}
}

void Boss_Colonel::Second_Attack_End()
{
	m_AttackCollider->Off();
}

void Boss_Colonel::First_Pattern_Start()
{
	// �ϴ� �ӽ÷� �̰ɷ��س��� 
	m_AnimationRender->ChangeAnimation("left_colonel_lightning");
	m_Sound = GameEngineResources::GetInst().SoundPlayToControl("lightning.wav");
	m_Sound.LoopCount(1);
	m_Sound.Volume(0.2f);

	if (false == m_Lightning)
	{
		Effect_Lightning* Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(GetPos() + float4{ -30 , -470 });
		
		m_Lightning = true;
	}
}

void Boss_Colonel::First_Pattern_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// �ִϸ��̼��� ������ ���� Ư�� ��ġ�� ����Ʈ������Ʈ����
		// ��ġ 6�� Ȯ���ؼ� ���� ���� 
		// 17809 , 978
		Effect_Lightning* Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(float4 { 17809 , 978});

		Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(float4{ 18109 , 978 });

		Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(float4{ 18409 , 978 });

		Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(float4{ 18709 , 978 });

		Effect = GetLevel()->CreateActor<Effect_Lightning>();
		Effect->SetPos(float4{ 19009 , 978 });
		
		ChangeState(BOSSSTATE::IDLE);
		return;
	}
}

void Boss_Colonel::First_Pattern_End()
{
	m_Lightning = false;
}

void Boss_Colonel::Death_Start()
{
	m_AnimationRender->ChangeAnimation("left_colonel_death");
}

void Boss_Colonel::Death_Update(float _DeltaTime)
{
	// �ϴ� �浹ü�� Off 
	if (true == m_Collider->IsUpdate())
	{
		m_Collider->Off();
	}
}

void Boss_Colonel::Death_End()
{
}

