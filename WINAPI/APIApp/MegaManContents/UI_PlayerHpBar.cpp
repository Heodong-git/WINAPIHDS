#include "UI_PlayerHpBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player_Zero.h"
#include "Boss_Colonel.h"
#include "ContentsEnum.h"

// 얘를 플레이어 HpBar 가 아니라 그냥 보스까지 포함해서 사용하면 될 거같은데

UI_PlayerHpBar::UI_PlayerHpBar()
{
}

UI_PlayerHpBar::~UI_PlayerHpBar()
{
}

// 스타트에서 렌더러 생성
void UI_PlayerHpBar::Start()
{
	m_PlayerHpRender = CreateRender(ZORDER::UI);
	m_PlayerHpRender->SetScale({ 320 * 4.0f , 240 * 4.0f });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_MAX" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_NINE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 1 , .End = 1 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_EIGHT" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 2 , .End = 2 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_SEVEN" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 3 , .End = 3 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_SIX" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 4 , .End = 4 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_FIVE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 5 , .End = 5 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_FOUR" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 6 , .End = 6 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_THREE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 7 , .End = 7 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_TWO" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 8 , .End = 8 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_ONE" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 9 , .End = 9 , .InterTime = 0.05f , .Loop = false });
	m_PlayerHpRender->CreateAnimation({ .AnimationName = "Player_Hp_ZERO" , .ImageName = "ui_hp_bar.bmp" ,
							.Start = 10 , .End = 10 , .InterTime = 0.05f , .Loop = false });

	m_PlayerHpRender->EffectCameraOff();
	m_PlayerHpRender->ChangeAnimation("Player_Hp_Max");

	// ------- 여기는 보스 

	m_BossHpRender = CreateRender(ZORDER::UI);
	m_BossHpRender->SetScale({ 320 * 4.0f , 240 * 4.0f });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_MAX" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 11 , .End = 11 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_NINE" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 13 , .End = 13 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_EIGHT" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 15 , .End = 15 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_SEVEN" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 17 , .End = 17 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_SIX" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 19 , .End = 19 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_FIVE" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 21 , .End = 21 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_FOUR" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 23 , .End = 23 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_THREE" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 25 , .End = 25 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_TWO" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 27 , .End = 27 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_ONE" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 29 , .End = 29 , .InterTime = 0.05f , .Loop = false });
	m_BossHpRender->CreateAnimation({ .AnimationName = "Boss_Hp_ZERO" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 31 , .End = 31 , .InterTime = 0.05f , .Loop = false });

	m_BossHpRender->EffectCameraOff();
	m_BossHpRender->Off();
	m_BossHpRender->ChangeAnimation("Boss_Hp_Max");
}

void UI_PlayerHpBar::Update(float _DeltaTime) 
{
	PlayerHpCheck();
	BossHpCheck();
}

void UI_PlayerHpBar::Render(float _DeltaTime)
{
	//// 디버깅용
	//HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	//float4 ActorPos = GetPos();

	//Rectangle(DoubleDC,
	//	ActorPos.ix() - 5,
	//	ActorPos.iy() - 5,
	//	ActorPos.ix() + 5,
	//	ActorPos.iy() + 5
	//);
}

void UI_PlayerHpBar::PlayerHpCheck()
{
	int PlayerHp = m_Player->GetHp();

	if (PlayerHp <= 0)
	{
		PlayerHp = 0;
	}

	switch (static_cast<HPSTATE>(PlayerHp))
	{
	case HPSTATE::MAX:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Max");
		break;
	case HPSTATE::NINE:
		m_PlayerHpRender->ChangeAnimation("player_Hp_NINE");
		break;
	case HPSTATE::EIGHT:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Eight");
		break;
	case HPSTATE::SEVEN:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Seven");
		break;
	case HPSTATE::SIX:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Six");
		break;
	case HPSTATE::FIVE:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Five");
		break;
	case HPSTATE::FOUR:
		m_PlayerHpRender->ChangeAnimation("player_Hp_Four");
		break;
	case HPSTATE::THREE:
		m_PlayerHpRender->ChangeAnimation("player_Hp_three");
		break;
	case HPSTATE::TWO:
		m_PlayerHpRender->ChangeAnimation("player_Hp_two");
		break;
	case HPSTATE::ONE:
		m_PlayerHpRender->ChangeAnimation("player_Hp_one");
		break;
	case HPSTATE::ZERO:
	{
		m_PlayerHpRender->ChangeAnimation("player_Hp_zero");
		if (nullptr != m_Player)
		{
			// 요기는 ChangeStateDeath 만들고
			// 죽는애니메이션 출력하고 
			// 애니메이션 출력끝나면 Death 로 변경? 하면되나?
			// m_Player->Death();
		}
	}
	break;
	}
}

void UI_PlayerHpBar::BossHpCheck()
{
	int BossHp = m_Boss->GetHp();

	if (0 >= BossHp)
	{
		BossHp = 0;
	}

	switch (static_cast<HPSTATE>(BossHp))
	{
	case HPSTATE::MAX:
		m_BossHpRender->ChangeAnimation("boss_Hp_Max");
		break;
	case HPSTATE::NINE:
		m_BossHpRender->ChangeAnimation("boss_Hp_NINE");
		break;
	case HPSTATE::EIGHT:
		m_BossHpRender->ChangeAnimation("boss_Hp_Eight");
		break;
	case HPSTATE::SEVEN:
		m_BossHpRender->ChangeAnimation("boss_Hp_Seven");
		break;
	case HPSTATE::SIX:
		m_BossHpRender->ChangeAnimation("boss_Hp_Six");
		break;
	case HPSTATE::FIVE:
		m_BossHpRender->ChangeAnimation("boss_Hp_Five");
		break;
	case HPSTATE::FOUR:
		m_BossHpRender->ChangeAnimation("boss_Hp_Four");
		break;
	case HPSTATE::THREE:
		m_BossHpRender->ChangeAnimation("boss_Hp_three");
		break;
	case HPSTATE::TWO:
		m_BossHpRender->ChangeAnimation("boss_Hp_two");
		break;
	case HPSTATE::ONE:
		m_BossHpRender->ChangeAnimation("boss_Hp_one");
		break;
	case HPSTATE::ZERO:
	{
		m_BossHpRender->ChangeAnimation("boss_Hp_zero");
		if (nullptr != m_Boss)
		{
			
		}
	}
	break;
	}
}
