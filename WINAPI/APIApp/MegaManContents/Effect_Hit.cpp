#include "Effect_Hit.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Effect_Hit::Effect_Hit()
{
}

Effect_Hit::~Effect_Hit()
{
}

void Effect_Hit::Start()
{
	// ----------------- 기본 이펙트

	m_HitRender = CreateRender(ZORDER::PLAYER_EFFECT);
	m_HitRender->SetPosition(float4{ 0, 0 });
	m_HitRender->SetScale(float4{ 400, 400 });

	// 애니메이션 이름 변경해야함
	m_HitRender->CreateAnimation({ .AnimationName = "wide_hit_effect" , .ImageName = "effect_hit.bmp",
									   .Start = 0 , .End = 3 , .InterTime = 0.06f , .Loop = false });
	m_HitRender->CreateAnimation({ .AnimationName = "diagonal_hit_effect" , .ImageName = "effect_hit.bmp",
									   .Start = 4 , .End = 7 , .InterTime = 0.06f , .Loop = false });
	m_HitRender->ChangeAnimation("wide_hit_effect");
}

void Effect_Hit::Update(float _DeltaTime)
{
	if (true == m_HitRender->IsAnimationEnd())
	{
		this->Death();
	}
}
