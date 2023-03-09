#include "Effect_Lightning.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "SpacePortLevel.h"
#include "Player_Zero.h"
#include "ContentsEnum.h"

Effect_Lightning::Effect_Lightning()
{
}

Effect_Lightning::~Effect_Lightning()
{
}

void Effect_Lightning::Start()
{
	m_AnimationRender = CreateRender(ZORDER::EFFECT);
	m_AnimationRender->SetScale(float4{ 100 , 1000 });

	m_AnimationRender->CreateAnimation({ .AnimationName = "lightning_effect" , .ImageName = "effect_lightning.bmp",
									   .Start = 0 , .End = 2 , .InterTime = 0.1f , .Loop = true });

	m_AnimationRender->ChangeAnimation("lightning_effect");

	m_Collider = CreateCollision(COLORDER::BOSSATTACK);
	m_Collider->SetDebugRenderType(CT_Rect);
	m_Collider->SetScale(float4{ 40, 1000 });
	m_Collider->SetPosition(float4{ 0 , -500 });

	m_AnimationRender->SetPosition(float4{ 0 , -m_Collider->GetScale().hy()});
}

void Effect_Lightning::Update(float _DeltaTime)
{
	if (0.0f >= m_LiveTime)
	{
		m_LiveTime = 0.0f;
		this->Death();
		return;
	}

	m_LiveTime -= _DeltaTime;

	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) , .TargetColType = CT_Rect , .ThisColType = CT_Rect}))
	{
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		if (nullptr != Level)
		{
			Player_Zero* Player = Level->GetPlayer();
			float4 PlayerPos = Player->GetPos();
			float Range = GetPos().x - PlayerPos.x;

			if (Range > 0.0f)
			{
				Player->Damage(2);
				Player->SetMove(float4::Left * 100.0f);
				Player->ChangeState(STATEVALUE::BIGHIT);
				return;
			}

			else if (Range <= 0.0f)
			{
				Player->Damage(2);
				Player->SetMove(float4::Right * 100.0f);
				Player->ChangeState(STATEVALUE::BIGHIT);
				return;
			}
		}
	}
}

void Effect_Lightning::Render(float _DeltaTime)
{
	//// µð¹ö±ë¿ë
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);
}
