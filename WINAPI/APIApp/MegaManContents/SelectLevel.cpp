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

// 1. 플레이할 캐릭터 
// 2. 배경화면
// 3. UI 
// 4. Sound 
void SelectLevel::Loading()
{
	// ENTER <-- 정수 13
	GameEngineInput::CreateKey("Change_SigmaStageLevel", 13);

	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리 존재여부 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 경로설정
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SelectLevel");
	
	// 백그라운드	
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
	if (true == GameEngineInput::IsDown("Change_SigmaStageLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SigmaStageLevel");
	}

	// 업데이트에서는 기본적으로 selectX 렌더가 선택되어 있고 그녀석의 애니메이션을 출력할건데.. 그건 
	// 여기가 아니라 selectx 액터에서 해야되는구나 
}
