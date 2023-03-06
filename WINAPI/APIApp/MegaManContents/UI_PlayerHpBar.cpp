#include "UI_PlayerHpBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player_Zero.h"
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
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_MAX" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_NINE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 1 , .End = 1 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_EIGHT" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 2 , .End = 2 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_SEVEN" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 3 , .End = 3 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_SIX" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 4 , .End = 4 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_FIVE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 5 , .End = 5 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_FOUR" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 6 , .End = 6 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_THREE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 7 , .End = 7 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_TWO" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 8 , .End = 8 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_ONE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 9 , .End = 9 , .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_Hp_ZERO" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 10 , .End = 10 , .InterTime = 0.05f , .Loop = false });

	m_AnimationRender->EffectCameraOff();
	m_AnimationRender->ChangeAnimation("Player_Hp_Max");
}

void UI_PlayerHpBar::Update(float _DeltaTime) 
{
	const int PlayerHp = m_Player->GetHp();

	switch (static_cast<HPSTATE>(PlayerHp))
	{
	case HPSTATE::MAX:
		m_AnimationRender->ChangeAnimation("player_Hp_Max");
		break;
	case HPSTATE::NINE:
		m_AnimationRender->ChangeAnimation("player_Hp_NINE");
		break;
	case HPSTATE::EIGHT:
		m_AnimationRender->ChangeAnimation("player_Hp_Eight");
		break;
	case HPSTATE::SEVEN:
		m_AnimationRender->ChangeAnimation("player_Hp_Seven");
		break;
	case HPSTATE::SIX:
		m_AnimationRender->ChangeAnimation("player_Hp_Six");
		break;
	case HPSTATE::FIVE:
		m_AnimationRender->ChangeAnimation("player_Hp_Five");
		break;
	case HPSTATE::FOUR:
		m_AnimationRender->ChangeAnimation("player_Hp_Four");
		break;
	case HPSTATE::THREE:
		m_AnimationRender->ChangeAnimation("player_Hp_three");
		break;
	case HPSTATE::TWO:
		m_AnimationRender->ChangeAnimation("player_Hp_two");
		break;
	case HPSTATE::ONE:
		m_AnimationRender->ChangeAnimation("player_Hp_one");
		break;
	case HPSTATE::ZERO:
	{
		m_AnimationRender->ChangeAnimation("player_Hp_zero");
		if (nullptr != m_Player)
		{
			// 요기는 ChangeStateDeath 만들고
			// 죽는애니메이션 출력하고 
			// 애니메이션 출력끝나면 Death 로 변경? 하면되나?
			m_Player->Death();
		}
	}
		break;
	}
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
