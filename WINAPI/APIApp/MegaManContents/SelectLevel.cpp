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
		GameEngineImage* Imgae = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_select_bar_x.bmp"));
		Imgae->Cut(3, 1);
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
		GameEngineImage* Imgae = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_ui_text_playerselect.bmp"));
	}
	
	// UI X 
	/*Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_zero.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_playerselect.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_x.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_zero.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_select_bar.bmp"));*/

	CreateActor<Select_BackGround>();
	CreateActor<UI_MainSelectUI>();
	/*CreateActor<UI_SelectX>();
	CreateActor<UI_SelectZero>();
	CreateActor<UI_TopText_PlayerSelect>();
	CreateActor<UI_BottomText_PlayerSelect>();
	CreateActor<UI_SelectBar>();*/
}

void SelectLevel::Update(float _DeltaTime)
{
	// ����ּ�
	/*if (true == GameEngineInput::IsDown("Change_SpacePortLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SpacePortLevel");
	}*/
}
