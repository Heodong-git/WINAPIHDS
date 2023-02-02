#include "UI_PlayerHpBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

UI_PlayerHpBar::UI_PlayerHpBar()
{
}

UI_PlayerHpBar::~UI_PlayerHpBar()
{
}

// 스타트에서 렌더러 생성
void UI_PlayerHpBar::Start()
{
	m_AnimationRender = CreateRender(ZORDER::UI);
	m_AnimationRender->SetScale({ 320 * 3.0f , 240 * 3.0f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hpbar0" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.15f });

	m_AnimationRender->ChangeAnimation("Player_Hpbar0");
}

void UI_PlayerHpBar::Update(float _DeltaTime)
{
}

void UI_PlayerHpBar::Render(float _DeltaTime)
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
