#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Select_BackGround.h"


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
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");

	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("Select");
		
	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Player_Select.bmp"));
	Image->Cut({ 7, 5 }, { 325,244 }, 1, 1);

	CreateActor<Select_BackGround>();
}

void SelectLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Change_SigmaStageLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SigmaStageLevel");
	}
}
