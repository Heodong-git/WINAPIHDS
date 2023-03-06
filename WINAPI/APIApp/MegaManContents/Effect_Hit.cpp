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
	m_AnimationRender = CreateRender(ZORDER::PLAYER_EFFECT);
	m_AnimationRender->SetPosition(float4{ 0, 0 });
	m_AnimationRender->SetScale(float4{ 400, 400 });

	// �ִϸ��̼� �̸� �����ؾ���
	m_AnimationRender->CreateAnimation({ .AnimationName = "wide_hit_effect" , .ImageName = "effect_hit.bmp",
									   .Start = 0 , .End = 3 , .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "diagonal_hit_effect" , .ImageName = "effect_hit.bmp",
									   .Start = 4 , .End = 7 , .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->ChangeAnimation("wide_hit_effect");
	
}

void Effect_Hit::Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		this->Death();
	}

	m_AnimationRender->ChangeAnimation("diagonal_hit_effect");
}
