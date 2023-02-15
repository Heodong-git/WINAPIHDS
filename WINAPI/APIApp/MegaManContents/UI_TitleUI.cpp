#include "UI_TitleUI.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_TitleUI::UI_TitleUI()
{
}

UI_TitleUI::~UI_TitleUI()
{
}

void UI_TitleUI::Start()
{
	// ----------------------------------- 메뉴 저장 --------------------------------------------------
	for (size_t i = 0; i < static_cast<size_t>(ETitleMenu::END); ++i)
	{
		// END 값이 3이기 때문에 총 세번 반복하게 되고
		// gamestart , continue , option 메뉴 세가지가 저장된다. 
		m_vecMenu.push_back(static_cast<ETitleMenu>(i));
	}

	m_CurMenu = m_vecMenu[m_CurIdx];

	// 애니메이션 추가 및 세팅
	// --------------------------------------메뉴 렌더러 -----------------------------------------------
	m_MenuRender = CreateRender("title_text.bmp", ZORDER::UI);
	m_MenuRender->CreateAnimation({ .AnimationName = "title_gamestart" , .ImageName = "title_text.bmp" ,
								.Start = 0 , .End = 0 });
	m_MenuRender->CreateAnimation({ .AnimationName = "title_CONTINUE" , .ImageName = "title_text.bmp" ,
								.Start = 1 , .End = 1 });
	m_MenuRender->CreateAnimation({ .AnimationName = "title_OPTION" , .ImageName = "title_text.bmp" ,
								.Start = 2 , .End = 2 });

	m_MenuRender->SetScale({ 320.0f * 1.5f, 240.0f * 1.5f } );
	m_MenuRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4 { 0.0f , 100.0f});
	m_MenuRender->ChangeAnimation("title_gamestart");


	// --------------------------------------press text 렌더러 ------------------------------------------
	m_TextRender = CreateRender("title_press_text.bmp", ZORDER::UI_Text);
	m_TextRender->CreateAnimation({ .AnimationName = "title_press_render" , .ImageName = "title_press_text.bmp" ,
									.Start = 0, .End = 1 , .InterTime = 0.6f });
	float4 ImageScale = m_TextRender->GetImage()->GetImageScale();
	m_TextRender->SetScale({ImageScale.x * 4 , ImageScale.y * 2});
	m_TextRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4{ 0.0f , 300.0f });
	m_TextRender->ChangeAnimation("title_press_render");
	
	GameEngineInput::CreateKey("title_up", VK_UP);
	GameEngineInput::CreateKey("title_down", VK_DOWN);
}

void UI_TitleUI::Update(float _DeltaTime)
{
	// 다운 키를 누르면 현재 enum값에서 다음 값으로 이동한다. 
	if (true == GameEngineInput::IsDown("title_down"))
	{
		// 키를 누른 시점에서 사운드 재생
		m_UISoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("player_select.wav");
		m_UISoundPlayer.LoopCount(1);
		m_UISoundPlayer.Volume(0.1f);

		// END = 현시점 3 
		++m_CurIdx;

		if (m_CurIdx == static_cast<int>(ETitleMenu::END))
		{
			m_CurIdx = static_cast<int>(ETitleMenu::GAMESTART);
			m_CurMenu = m_vecMenu[m_CurIdx];
			return;
		}

		m_CurMenu = m_vecMenu[m_CurIdx];
	}

	if (true == GameEngineInput::IsDown("title_up"))
	{
		// 키를 누른 시점에서 사운드 재생
		m_UISoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("player_select.wav");
		m_UISoundPlayer.LoopCount(1);
		m_UISoundPlayer.Volume(0.1f);

		--m_CurIdx;
		
		if (m_CurIdx < static_cast<int>(ETitleMenu::GAMESTART))
		{
			m_CurIdx = static_cast<int>(ETitleMenu::OPTION);
			m_CurMenu = m_vecMenu[m_CurIdx];
			return;
		}

		m_CurMenu = m_vecMenu[m_CurIdx];
	}	

	switch (m_CurMenu)
	{
	case ETitleMenu::GAMESTART:
	{
		m_MenuRender->ChangeAnimation("title_gamestart");
		
	}
		break;
	case ETitleMenu::CONTINUE:
		m_MenuRender->ChangeAnimation("title_continue");
		break;
	case ETitleMenu::OPTION:
		m_MenuRender->ChangeAnimation("title_option");
		break;
	}
}

void UI_TitleUI::Render(float _DeltaTime)
{
}
