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
	// 보고다시 
	m_Collider = CreateCollision(COLORDER::BOSS);
	m_Collider->SetScale(float4{ 200, 200 });
	m_Collider->SetPosition({ 0, -100 });
	
	m_AttackCollider = CreateCollision(COLORDER::BOSSATTACK);
	m_AttackCollider->SetScale(float4{ 250, 250 });
	m_AttackCollider->Off();
}

void Boss_Colonel::Update(float _DeltaTime)
{
	// 여기서 플레이어가 fight 상태가 아니라면 업데이트 하지말고 return 

	UpdateState(_DeltaTime);

	if (true == m_Invincibility)
	{
		if (m_InvincibilityTime >= m_MaxInvincibility)
		{
			m_InvincibilityTime = 0.0f;
			m_Invincibility = false;
		}

		m_InvincibilityTime += _DeltaTime;
	}

	// 단일 충돌체크 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// 무적이 아닐때만 
		if (false == m_Invincibility)
		{
			// 무적상태로 변경
			m_Invincibility = true;
			SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		
			if (nullptr != Level)
			{
				// 플레이어의 x 축위치가 
				float4 PlayerPos = Level->GetPlayer()->GetPos();
				float Range = GetPos().x - PlayerPos.x;
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

	
}

void Boss_Colonel::Render(float _DeltaTime)
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

void Boss_Colonel::AnimDirCheck(const std::string_view& _AnimationName)
{
	// 현재 방향문자열 값을 받아온다. 
	std::string PrevDirString = m_DirString;
	// 해당하는 방향의 애니메이션으로 change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());

	// 플레이어의 위치가 나보다 왼쪽에 있다면 ~ 오른쪽에 있다면 ~ 코드 작성해야함 
	SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
	// 범위안에 들어왔다면 shot state로 변경인데.. 흠
	if (nullptr != Level)
	{
		// 플레이어 위치를 받아왔어
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float Range = GetPos().x - PlayerPos.x;
		if (0 >= Range)
		{
			m_DirString = "Right_";
		}

		else if (0 < Range)
		{
			m_DirString = "Left_";
		}
	}

}

void Boss_Colonel::ChangeState(BOSSSTATE _State)
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
	// 전투시작모션
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Start" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });
	// 기본자세 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_idle" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 2 , .End = 4 , .InterTime = 0.2f });
	// 텔레포트 left 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Teleport" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 5 , .End = 8 , .InterTime = 0.14f , .Loop = true });
	// 평타 1타
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_first_attack" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 9 , .End = 13 , .InterTime = 0.08f });

	// 평타 2타
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_second_attack" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 14 , .End = 19 , .InterTime = 0.08f });

	// 전격 패턴
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_lightning" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 21 , .End = 38 , .InterTime = 0.08f });

	// 데스 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Left_Colonel_Death" , .ImageName = "spaceport_colonel_left.bmp" ,
							.Start = 45 , .End = 45 , .InterTime = 0.08f , .Loop = false });


	// 오른쪽 -----------------------------------------

	// 전투시작모션
	m_AnimationRender->CreateAnimation({ .AnimationName = "Right_Colonel_Start" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });

	// 기본자세 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_idle" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 2 , .End = 4 , .InterTime = 0.2f });

	// 텔레포트 right 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_Teleport" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 5 , .End = 8, .InterTime = 0.14f , .Loop = false });

	// 공격1타 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_first_attack" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 9 , .End = 13, .InterTime = 0.08f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_second_attack" , .ImageName = "spaceport_colonel_right.bmp" ,
								.Start = 14 , .End = 19, .InterTime = 0.08f , .Loop = false });

	// 데스 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_Colonel_Death" , .ImageName = "spaceport_colonel_right.bmp" ,
							.Start = 45 , .End = 45 , .InterTime = 0.08f , .Loop = false });

	
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

	if (true == IsHpZero())
	{
		ChangeState(BOSSSTATE::DEATH);
		return;
	}

	if (true == m_SkillUse)
	{
		m_SkillCoolDown -= _DeltaTime;

		if (m_SkillCoolDown <= 0.0f)
		{
			m_SkillCoolDown = m_SkillCoolDownMax;
			m_SkillUse = false;
		}
	}


	// 여기서 스타트 모션이 끝나면 Hp바를 보이게해 
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


	float4 Pos = GetPos();
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
}

void Boss_Colonel::Teleport_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// 순간이동 애니메이션이 끝나면 플레이어의 앞, 혹은 뒤로 이동해서 공격
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// 범위안에 들어왔다면 shot state로 변경인데.. 흠
		if (nullptr != Level)
		{
			// 플레이어 x축만 가지고 어떻게 안되나?? 어 흠
			// 일단 이렇게해 
			float4 PlayerPos = Level->GetPlayer()->GetPos();
			float PlayerPosX = PlayerPos.x;
			SetPos(PlayerPos + float4 { 200, 0 });
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

	// 여기서는 플레이어처럼 충돌체 만들어야함 
	m_AttackCollider->On();
	m_AttackCollider->SetPosition(float4{ -150, -100 });
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

	// 여기서는 플레이어처럼 충돌체 만들어야함 
	m_AttackCollider->On();
	m_AttackCollider->SetPosition(float4{ -150, -100 });
}

void Boss_Colonel::Second_Attack_End()
{
	m_AttackCollider->Off();
}

void Boss_Colonel::First_Pattern_Start()
{
	// 일단 임시로 이걸로해놓고 
	m_AnimationRender->ChangeAnimation("left_colonel_lightning");
}

void Boss_Colonel::First_Pattern_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(BOSSSTATE::IDLE);
		return;
	}
}

void Boss_Colonel::First_Pattern_End()
{
}

void Boss_Colonel::Death_Start()
{
	m_AnimationRender->ChangeAnimation("left_colonel_death");
}

void Boss_Colonel::Death_Update(float _DeltaTime)
{
	// 일단 충돌체를 Off 
	m_Collider->Off();
}

void Boss_Colonel::Death_End()
{
}

