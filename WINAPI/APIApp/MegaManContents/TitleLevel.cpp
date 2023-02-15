#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Title_BackGround.h"
#include "UI_TitleUI.h"
#include "ContentsEnum.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

// Ÿ��Ʋ������ �ε����� �ʿ��� ��?
// 1. UI
// 2. ���ȭ��
// 3. Sound ?
void TitleLevel::Loading()
{
	// ENTER <-- ���� 13
	GameEngineInput::CreateKey("Change_Level", 13);
	GameEngineDirectory Directory;
	// ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");

	// ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("TitleLevel");

	// Ÿ��Ʋ�̹��� 
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));
	
	{
		// Ÿ��Ʋ �޴�
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("title_text.bmp"));
		Image->Cut(2, 2);
	}
	{
		// �ϴ� �ؽ�Ʈ
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("title_press_text.bmp"));
		Image->Cut(1, 2);
	}

	{
		// ���Ž�� 
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentsResources");
		Dir.Move("ContentsResources");
		Dir.Move("Sound");
		Dir.Move("TitleLevel");

		// ���� �ε� 
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("title_menu_select.wav"));
		GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("title_menu_select_complete.wav"));
	}
	CreateActor<Title_BackGround>();

	// ������ ���� UI�� ������ �ְ� �ϰ�, �޴� ���ýÿ�
	// ���õǾ� �ִ� �޴��� �޾ƿͼ� �޴��� ���� ���۽�Ų��.	
	m_TitleUI = CreateActor<UI_TitleUI>();
}

void TitleLevel::Update(float _DeltaTime)
{
	// Ÿ��Ʋ���������� ENTER Ű�� �Է��ϸ� SelectStage �� Level ��ȯ
	if (true == GameEngineInput::IsDown("Change_Level"))
	{
		// ����޴��� �޾ƿ���. 
		ETitleMenu Menu = m_TitleUI->GetCurMenuType();

		// �޴� Ÿ�Կ� ���� �б�ó�� 
		switch (Menu)

		{
		case ETitleMenu::GAMESTART:
		{
			GameEngineCore::GetInst()->ChangeLevel("SelectLevel");
			BGMPlayer.Stop();

			BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("title_menu_select_complete.wav");
			BGMPlayer.LoopCount(1);
			BGMPlayer.Volume(0.3f);
		}
			break;
		case ETitleMenu::CONTINUE:
			break;
		case ETitleMenu::OPTION:
			break;
		}
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// �������
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Title.wav");
	BGMPlayer.LoopCount(1);
	BGMPlayer.Volume(0.1f);
	/*
	UISoundPlayer = GameEngineResources::GetInst().SoundPlayToControl("player_select.wav");
	UISoundPlayer.LoopCount(1);
	UISoundPlayer.Volume(0.1f);*/
}
