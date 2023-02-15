#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Select_BackGround.h"
#include "UI_MainSelectUI.h"

SelectLevel::SelectLevel() 
{
}

SelectLevel::~SelectLevel()
{
}

// 1. �÷����� ĳ���� 
// 2. ���ȭ��
// 3. UI 
// 4. Sound 
void SelectLevel::Loading()
{
	// ENTER <-- ���� 13
	GameEngineInput::CreateKey("Change_SpacePortLevel", 13);

	GameEngineDirectory Directory;
	// ���������� �ش� ���͸� ���翩�� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// ��μ���
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SelectLevel");
	
	// ��׶���	
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

	{
		// ���Ž�� 
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Sound");
		Dir.Move("Select");

		// ���� �ε� 
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_select.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_select_complete.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_select_bgm.wav"));
	}
	
	// ---------------------- ������ʹ� Spaceport Level ���� ����� �̹��� ������ �ε� ----------------------------------
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

	if (true == GameEngineInput::IsDown("Change_SpacePortLevel"))
	{
		m_BGMSound.Stop();
		m_SelectComplete = GameEngineResources::GetInst().SoundPlayToControl("player_select_complete.wav");
		m_SelectComplete.LoopCount(1);
		m_SelectComplete.Volume(0.2f);

		if (ESelectPlayer::ZERO == m_MainSelectUI->GetSelectPlayer())
		{
			m_ChangeLevel = true;
		}
	}
}

void SelectLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// �������
	m_BGMSound = GameEngineResources::GetInst().SoundPlayToControl("Player_Select_BGM.wav");
	m_BGMSound.LoopCount(100);
	m_BGMSound.Volume(0.1f);
}
