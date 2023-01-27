#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Select_BackGround.h"
#include "UI_MainSelectUI.h"

SelectLevel::SelectLevel() 
{
}

SelectLevel::~SelectLevel()
{
}

// 1. 플레이할 캐릭터 
// 2. 배경화면
// 3. UI 
// 4. Sound 
void SelectLevel::Loading()
{
	// ENTER <-- 정수 13
	GameEngineInput::CreateKey("Change_SpacePortLevel", 13);

	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리 존재여부 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 경로설정
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SelectLevel");
	
	// 백그라운드	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_background.bmp"));
	}
	{
		// X UI
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_x.bmp"));
	}
	{
		// Zero UI
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_zero.bmp"));
	}
	{
		// select bar zero
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_select_bar_zero.bmp"));
		Image->Cut(3, 1);
	}
	{
		// select bar X 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_select_bar_x.bmp"));
		Image->Cut(3, 1);
	}
	{
		// select text X 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_ui_text_X.bmp"));
	}
	{
		// select text zero 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_ui_text_zero.bmp"));
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_ui_text_playerselect.bmp"));
	}
	{
		// left idle 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_player_idle_walk_left.bmp"));
		Image->Cut(8, 3);	
	}
	{
		// attack right 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_player_attack_right.bmp"));
		Image->Cut(8, 4);
	}
	{
		// attack left
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_player_attack_left.bmp"));
		Image->Cut(8, 4);
	}
	{
		// exit 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_player_exit.bmp"));
		Image->Cut(8, 2);
	}
	
	// ---------------------- 여기부터는 Spaceport Level 에서 사용할 이미지 편집용 로드 ----------------------------------
	{
		// GameEngineImage* TestImage = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName(""))
	}

	CreateActor<Select_BackGround>();
	m_MainSelectUI = CreateActor<UI_MainSelectUI>();
}

void SelectLevel::Update(float _DeltaTime)
{
	if (true == m_ChangeLevel)
	{
		m_ChangeTime += _DeltaTime;
	}

	if (1.03f <= m_ChangeTime)
	{
		GameEngineCore::GetInst()->ChangeLevel("SpacePortLevel");
		m_ChangeTime = 0.0f;
	}

	// 엔터를 쳤을 때 현재 선택된 캐릭터가 엑스라면 시작하면 retrun 해야함 
	if (true == GameEngineInput::IsDown("Change_SpacePortLevel"))
	{
		if (ESelectPlayer::ZERO == m_MainSelectUI->GetSelectPlayer())
		{
			m_ChangeLevel = true;
		}
	}
}
