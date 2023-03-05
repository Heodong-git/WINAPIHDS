#include "Effect_Dash.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpacePortLevel.h"
#include "Player_Zero.h"
#include "ContentsEnum.h"
Effect_Dash::Effect_Dash()
{
}

Effect_Dash::~Effect_Dash()
{
}

void Effect_Dash::Start()
{
	m_AnimationRender = CreateRender(ZORDER::PLAYER_EFFECT);
	m_AnimationRender->SetPosition(float4{ 0, 0 });
	m_AnimationRender->SetScale(float4{ 500, 500 });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_dash_effect" , .ImageName = "effect_dash_right.bmp",
									   .Start = 0 , .End = 7 , .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash_effect" , .ImageName = "effect_dash_left.bmp",
									   .Start = 0 , .End = 7 , .InterTime = 0.06f , .Loop = false });
}

void Effect_Dash::Update(float _DeltaTime)
{
	if (m_AnimationRender->IsAnimationEnd())
	{
		this->Death();
	}
}
