#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Title_BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

// 타이틀레벨의 로딩에서 필요한 것?
// 1. UI
// 2. 배경화면
// 3. Sound ?
void TitleLevel::Loading()
{
	// ENTER <-- 정수 13
	GameEngineInput::CreateKey("Change_SelectLevel", 13);
	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");

	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("TitleLevel");

	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));

	CreateActor<Title_BackGround>();
}

void TitleLevel::Update(float _DeltaTime)
{
	// 타이틀레벨에서는 ENTER 키를 입력하면 SelectStage 로 Level 전환
	if (true == GameEngineInput::IsDown("Change_SelectLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectLevel");
	}
}
