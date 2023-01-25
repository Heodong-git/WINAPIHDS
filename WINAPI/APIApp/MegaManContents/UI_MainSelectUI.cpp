#include "UI_MainSelectUI.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_MainSelectUI::UI_MainSelectUI()
{
}

UI_MainSelectUI::~UI_MainSelectUI()
{
}

void UI_MainSelectUI::Start()
{
	float4 ScreenSizeHalf = GameEngineWindow::GetScreenSize().half();

	// X select UI 
	m_SelectX = CreateRender(RENDERORDER::UI);
	m_SelectX->SetImage("select_UI_X.bmp");
	m_SelectX->SetScaleToImage();
	m_SelectX->SetPosition(ScreenSizeHalf + float4 { -250.0f ,  0.0f});

	// Zero select UI
	m_SelectZero = CreateRender(RENDERORDER::UI);
	m_SelectZero->SetImage("select_UI_zero.bmp");
	m_SelectZero->SetScaleToImage();
	m_SelectZero->SetPosition(ScreenSizeHalf + float4{ 250.0f , 0.0f });

	// 초록색 Select Bar 
	m_SelectBar = CreateRender("select_select_bar_zero.bmp", RENDERORDER::UI);
	m_SelectBar->CreateAnimation({ .AnimationName = "select_zero" , .ImageName = "select_select_bar_zero.bmp",
								   .Start = 0 , .End = 2 , .InterTime = 0.05f });
	m_SelectBar->SetScale({ ScreenSizeHalf.x * 1.3f , ScreenSizeHalf.y * 1.42f });
	m_SelectBar->SetPosition(ScreenSizeHalf + float4 { 250.0f , -8.0f});
	m_SelectBar->ChangeAnimation("select_zero");

	// X, Zero 텍스트
	m_TextX = CreateRender(RENDERORDER::UI_Text);
	m_TextX->SetImage("select_UI_Text_X.bmp");
	m_TextX->SetScale(m_TextX->GetImage()->GetImageScale() * 2.0f);
	m_TextX->SetPosition(ScreenSizeHalf + float4{ -250.f , 260.0f });

	m_TextZero = CreateRender(RENDERORDER::UI_Text);
	m_TextZero->SetImage("select_UI_Text_Zero.bmp");
	m_TextZero->SetScale(m_TextZero->GetImage()->GetImageScale() * 2.0f);
	m_TextZero->SetPosition(ScreenSizeHalf + float4{ 350.f , 270.0f });
}

void UI_MainSelectUI::Update(float _DeltaTime)
{
}

void UI_MainSelectUI::Render(float _DeltaTime)
{
}
