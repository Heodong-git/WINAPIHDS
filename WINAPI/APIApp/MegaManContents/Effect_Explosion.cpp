#include "Effect_Explosion.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Effect_Explosion::Effect_Explosion()
{
}

Effect_Explosion::~Effect_Explosion()
{
}

void Effect_Explosion::Start()
{
	m_AnimationRender = CreateRender(ZORDER::EFFECT);
	m_AnimationRender->SetPosition(float4{ 0, 0 });
	m_AnimationRender->SetScale(float4{ 500, 500 });

	// 애니메이션 만들어야함 
	m_AnimationRender->CreateAnimation({ .AnimationName = "explosion_effect" , .ImageName = "effect_explosion.bmp",
									   .Start = 0 , .End = 9 , .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->ChangeAnimation("explosion_effect");
}

void Effect_Explosion::Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		this->Death();
	}
	
	m_AnimationRender->ChangeAnimation("explosion_effect");
}

