#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Select_BackGround.h"
#include "UI_SelectX.h"
#include "UI_SelectZero.h"
#include "UI_TopText_PlayerSelect.h"
#include "UI_BottomText_PlayerSelect.h"
#include "UI_SelectBar.h"
#include "Player_Zero.h"

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
	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_background.bmp"));
	// UI X 
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_x.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_zero.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_playerselect.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_x.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_UI_text_zero.bmp"));
	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_select_bar.bmp"));
	Image->Cut({ 0, 0 }, { 628 , 170 }, 3, 1);

	Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("select_player_attack_left.bmp"));
	Image->Cut({ 124, 15 }, { 1557, 151 }, 8, 1);

	CreateActor<Select_BackGround>();
	CreateActor<UI_SelectX>();
	CreateActor<UI_SelectZero>();
	CreateActor<UI_TopText_PlayerSelect>();
	CreateActor<UI_BottomText_PlayerSelect>();
	CreateActor<UI_SelectBar>();
}

void SelectLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Change_SpacePortLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SpacePortLevel");
	}

	// ������Ʈ������ �⺻������ selectX ������ ���õǾ� �ְ� �׳༮�� �ִϸ��̼��� ����Ұǵ�.. �װ� 
	// ���Ⱑ �ƴ϶� selectx ���Ϳ��� �ؾߵǴ±��� 
}
