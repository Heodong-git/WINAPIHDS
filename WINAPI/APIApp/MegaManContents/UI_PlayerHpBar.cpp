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
	m_AnimationRender->SetScale({ 320 * 4.0f , 240 * 4.0f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.6f , .Loop = false });

	m_AnimationRender->EffectCameraOff();
	
	/*m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 1 , .End = 1 , .InterTime = 0.6f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 2 , .End = 2 , .InterTime = 0.6f });*/

	m_AnimationRender->ChangeAnimation("Player_HpbarMax");
}

void UI_PlayerHpBar::Update(float _DeltaTime) 
{
	float4 Pos = GetPos();
	int a = 0;
}

void UI_PlayerHpBar::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
