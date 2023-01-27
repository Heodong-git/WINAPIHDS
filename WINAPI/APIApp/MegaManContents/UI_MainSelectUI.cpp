#include "UI_MainSelectUI.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"


// �̰ű����ϸ� selectlevel�� �ϴ� ������
// ���͸� ġ�� ��׶��带 ������ ��� UI�� �������
// ������ ��� �ִϸ��̼��� ����ǰ��� Play Stage�� �̵��Ѵ�. 

float UI_MainSelectUI::m_Time = 0.0f;

UI_MainSelectUI::UI_MainSelectUI()
{
}

UI_MainSelectUI::~UI_MainSelectUI()
{
}

void UI_MainSelectUI::Start()
{
	// ������ ������ ���ݰ� 
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

	// �ʷϻ� Select Bar 
	m_SelectBar = CreateRender("select_select_bar_zero.bmp", RENDERORDER::UI);
	m_SelectBar->CreateAnimation({ .AnimationName = "select_zero" , .ImageName = "select_select_bar_zero.bmp",
								   .Start = 0 , .End = 2 , .InterTime = 0.05f });
	m_SelectBar->CreateAnimation({ .AnimationName = "select_X", .ImageName = "select_select_bar_X.bmp" ,
								   .Start = 0, .End = 2, .InterTime = 0.05f });

	// X �ؽ�Ʈ
	m_TextX = CreateRender(RENDERORDER::UI_Text);
	m_TextX->SetImage("select_UI_Text_X.bmp");
	m_TextX->SetScale(m_TextX->GetImage()->GetImageScale() * 2.0f);
	m_TextX->SetPosition(m_ScreenSizeHalf + float4{ -250.f , 260.0f });

	// Zero �ؽ�Ʈ
	m_TextZero = CreateRender(RENDERORDER::UI_Text);
	m_TextZero->SetImage("select_UI_Text_Zero.bmp");
	m_TextZero->SetScale(m_TextZero->GetImage()->GetImageScale() * 2.0f);
	m_TextZero->SetPosition(m_ScreenSizeHalf + float4{ 350.f , 270.0f });

	// Top �ؽ�Ʈ
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

	// ���� �ִϸ��̼�
	// �ȼ������Ұ� �ӽ÷� ����
	m_ZeroAnimation = CreateRender(RENDERORDER::PLAYER);
	m_ZeroAnimation->CreateAnimation({ .AnimationName = "select_idle_left" , .ImageName = "select_player_idle_walk_left.bmp" ,
									  .Start = 0, .End = 5 , .InterTime = 0.15f });
	m_ZeroAnimation->CreateAnimation({ .AnimationName = "select_attack_left", .ImageName = "select_player_attack_left.bmp" ,
									   .Start = 0, .End = 28, .InterTime = 0.035f});
	m_ZeroAnimation->CreateAnimation({ .AnimationName = "select_attack_right", .ImageName = "select_player_attack_right.bmp" ,
									   .Start = 0, .End = 28, .InterTime = 0.035f });
	m_ZeroAnimation->CreateAnimation({ .AnimationName = "select_exit", .ImageName = "select_player_exit.bmp" ,
									   .Start = 0, .End = 13, .InterTime = 0.06f, .Loop = false });

	m_ZeroAnimation->SetScale({640.0f, 480.0f * 1.5f });
	m_ZeroAnimation->SetPosition(m_ScreenSizeHalf + float4{ 550.0f, 300.0f });
	m_ZeroAnimation->ChangeAnimation("select_idle_left");

	
	// �¿� Ű����
	GameEngineInput::CreateKey("SelectMove_Right", VK_RIGHT);
	GameEngineInput::CreateKey("SelectMove_Left", VK_LEFT);
	GameEngineInput::CreateKey("Select_Enter", 13);
}

void UI_MainSelectUI::Update(float _DeltaTime)
{
	// ĳ���ͼ��þ�����Ʈ
	SelectUpdate(_DeltaTime);
	TopBottomTextUpdate(_DeltaTime);
}

void UI_MainSelectUI::Render(float _DeltaTime)
{
}

void UI_MainSelectUI::SelectUpdate(float _DeltaTime)
{
	// ���� ���Ͱ����ȴٸ� ����ü���� + ���� UI �� �ʿ��� �ִϸ��̼� ����
	// ���ξִϸ��̼� , ��׶��� ������ ������ ���༮�� �������� �ȵǰ��Ϸ���
	// �������·� ���������� �ʳ�? 

	if (true == GameEngineInput::IsDown("Select_Enter"))
	{
		if (ESelectPlayer::ZERO == GetSelectPlayer())
		{
			m_ZeroAnimation->ChangeAnimation("Select_exit");
		}
	}

	if (true == GameEngineInput::IsDown("SelectMove_Right"))
	{
		if (ESelectPlayer::X == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::ZERO;
			m_ZeroAnimation->ChangeAnimation("select_attack_left");
		}
		else if (ESelectPlayer::ZERO == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::X;
			m_ZeroAnimation->ChangeAnimation("select_idle_left");
		}
	}

	if (true == GameEngineInput::IsDown("SelectMove_Left"))
	{
		if (ESelectPlayer::ZERO == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::X;
			m_ZeroAnimation->ChangeAnimation("select_idle_left");
		}
		else if (ESelectPlayer::X == m_SelectPlayer)
		{
			m_SelectPlayer = ESelectPlayer::ZERO;
			m_ZeroAnimation->ChangeAnimation("select_attack_left");
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
	// �ð����� 
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
