#include "UI_MainSelectUI.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"


float UI_MainSelectUI::m_Time = 0.0f;

UI_MainSelectUI::UI_MainSelectUI()
{
}

UI_MainSelectUI::~UI_MainSelectUI()
{
}

void UI_MainSelectUI::Start()
{
	// 윈도우 사이즈 절반값 
	m_ScreenSize = GameEngineWindow::GetScreenSize();
	m_ScreenSizeHalf = m_ScreenSize.half();

	// X select UI 
	m_SelectX = CreateRender(RENDERORDER::UI);
	m_SelectX->SetImage("select_UI_X.bmp");
	m_SelectX->SetScaleToImage();
	m_SelectX->SetPosition(m_ScreenSizeHalf + float4 { -250.0f ,  0.0f});

	// Zero select UI
	m_SelectZero = CreateRender(RENDERORDER::UI);
	m_SelectZero->SetImage("select_UI_zero.bmp");
	m_SelectZero->SetScaleToImage();
	m_SelectZero->SetPosition(m_ScreenSizeHalf + float4{ 250.0f , 0.0f });

	// 초록색 Select Bar 
	m_SelectBar = CreateRender("select_select_bar_zero.bmp", RENDERORDER::UI);
	m_SelectBar->CreateAnimation({ .AnimationName = "select_zero" , .ImageName = "select_select_bar_zero.bmp",
								   .Start = 0 , .End = 2 , .InterTime = 0.05f });
	m_SelectBar->CreateAnimation({ .AnimationName = "select_X", .ImageName = "select_select_bar_X.bmp" ,
								   .Start = 0, .End = 2, .InterTime = 0.05f });

	// X 텍스트
	m_TextX = CreateRender(RENDERORDER::UI_Text);
	m_TextX->SetImage("select_UI_Text_X.bmp");
	m_TextX->SetScale(m_TextX->GetImage()->GetImageScale() * 2.0f);
	m_TextX->SetPosition(m_ScreenSizeHalf + float4{ -250.f , 260.0f });

	// Zero 텍스트
	m_TextZero = CreateRender(RENDERORDER::UI_Text);
	m_TextZero->SetImage("select_UI_Text_Zero.bmp");
	m_TextZero->SetScale(m_TextZero->GetImage()->GetImageScale() * 2.0f);
	m_TextZero->SetPosition(m_ScreenSizeHalf + float4{ 350.f , 270.0f });

	// Top 텍스트
	m_TopText = CreateRender(RENDERORDER::UI_Text);
	m_TopText->SetImage("select_UI_text_playerselect.bmp");
	m_TopText->SetScale(m_TopText->GetImage()->GetImageScale() * 1.5f);
	m_TopTextStartPos = { m_ScreenSize.x + 450.f , 100.0f };
	m_TopText->SetPosition(m_TopTextStartPos);

	m_BottomText = CreateRender(RENDERORDER::UI_Text);
	m_BottomText->SetImage("select_UI_text_playerselect.bmp");
	m_BottomText->SetScale(m_TopText->GetImage()->GetImageScale() * 1.5f);
	m_BottomTextStartPos = { -450.0f , 850.0f };
	m_BottomText->SetPosition(m_BottomTextStartPos);

	// 제로 애니메이션
	// m_ZeroAnimation = CreateRender(RENDERORDER::PLAYER);

	// 좌우 키생성
	GameEngineInput::CreateKey("SelectMove_Right", VK_RIGHT);
	GameEngineInput::CreateKey("SelectMove_Left", VK_LEFT);
}

void UI_MainSelectUI::Update(float _DeltaTime)
{
	// 캐릭터선택업데이트
	SelectUpdate(_DeltaTime);
	TopBottomTextUpdate(_DeltaTime);
}

void UI_MainSelectUI::Render(float _DeltaTime)
{
}

void UI_MainSelectUI::SelectUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("SelectMove_Right"))
	{
		if (ESelectPlayer::X == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::ZERO;
		}
		else if (ESelectPlayer::ZERO == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::X;
		}
	}

	if (true == GameEngineInput::IsDown("SelectMove_Left"))
	{
		if (ESelectPlayer::ZERO == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::X;
		}
		else if (ESelectPlayer::X == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::ZERO;
		}
	}


	switch (m_SelectPlayer)
	{
	case ESelectPlayer::X:
	{
		m_SelectBar->SetScale({ m_ScreenSizeHalf.x * 1.3f , m_ScreenSizeHalf.y * 1.5f });
		m_SelectBar->SetPosition(m_ScreenSizeHalf + float4{ -250.0f , 3.0f });
		m_SelectBar->ChangeAnimation("select_x");
	}
	break;
	case ESelectPlayer::ZERO:
		m_SelectBar->SetScale({ m_ScreenSizeHalf.x * 1.3f , m_ScreenSizeHalf.y * 1.42f });
		m_SelectBar->SetPosition(m_ScreenSizeHalf + float4{ 250.0f , -8.0f });
		m_SelectBar->ChangeAnimation("select_zero");
		break;
	}
}

void UI_MainSelectUI::TopBottomTextUpdate(float _DeltaTime)
{
	// 시간누적 
	m_Time += _DeltaTime;

	if (m_TextMoveTime <= m_Time)
	{
		m_TopText->SetPosition(m_TopTextStartPos);
		m_BottomText->SetPosition(m_BottomTextStartPos);
		m_Time = 0.0f;
	}
	
	if (m_TextMoveTime >= m_Time)
	{
		m_TopText->MovePosition(float4::Left * _DeltaTime * m_TextMoveSpeed);
		m_BottomText->MovePosition(float4::Right * _DeltaTime * m_TextMoveSpeed);
	}

	
	
}
