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

	// 여기부터다시. 
	// 카메라가 움직이면 카메라와 똑같이 이동하면 될듯. 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 35 , .InterTime = 0.6f });
	
	/*m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 1 , .End = 1 , .InterTime = 0.6f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 2 , .End = 2 , .InterTime = 0.6f });*/

	m_AnimationRender->ChangeAnimation("Player_HpbarMax");
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
