#include "Effect_Boss_Hit.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Effect_Boss_Hit::Effect_Boss_Hit()
{
}

Effect_Boss_Hit::~Effect_Boss_Hit()
{
}

void Effect_Boss_Hit::Start()
{
	//  ----------------- 보스 히트 이펙트 
	m_EffectRender = CreateRender(ZORDER::PLAYER_EFFECT);
	m_EffectRender->SetPosition(float4{ 0 , 0 });
	m_EffectRender->SetScale(float4{ 500, 500 });

	m_EffectRender->CreateAnimation({ .AnimationName = "left_blade_hit_effect" , .ImageName = "effect_blade_left.bmp",
									   .Start = 8 , .End = 12 , .InterTime = 0.08f , .Loop = false });
	m_EffectRender->CreateAnimation({ .AnimationName = "right_blade_hit_effect" , .ImageName = "effect_blade_right.bmp",
									   .Start = 8 , .End = 12 , .InterTime = 0.08f , .Loop = false });
}

void Effect_Boss_Hit::Update(float _DeltaTime)
{
	if (true == m_EffectRender->IsAnimationEnd())
	{
		this->Death();
	}
}
