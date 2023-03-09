#include "Effect_wall.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

Effect_wall::Effect_wall()
{
}

Effect_wall::~Effect_wall()
{
}

void Effect_wall::Start()
{
	m_AnimationRender = CreateRender(ZORDER::EFFECT);
	m_AnimationRender->SetScale(float4{ 200, 200 });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall_slip" , .ImageName = "effect_wall_slip_right.bmp" ,
								.Start = 0 , .End = 7 , .InterTime = 0.06f });
	m_AnimationRender->ChangeAnimation("right_wall_slip");
}

void Effect_wall::Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		this->Death();
	}
}

void Effect_wall::Render(float _DeltaTime)
{
	// µð¹ö±ë¿ë
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);
}
