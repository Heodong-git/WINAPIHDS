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

// 타이틀레벨의 로딩에서 필요한 것?
// 1. UI
// 2. 배경화면
// 3. Sound ?
void TitleLevel::Loading()
{
	// ENTER <-- 정수 13
	GameEngineInput::CreateKey("Change_Level", 13);
	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");

	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("TitleLevel");

	// 타이틀이미지 
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));
	
	{
		// 타이틀 메뉴
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("title_text.bmp"));
		Image->Cut(2, 2);
	}
	{
		// 하단 텍스트
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("title_press_text.bmp"));
		Image->Cut(1, 2);
	}

	CreateActor<Title_BackGround>();
	m_TitleUI = CreateActor<UI_TitleUI>();
}

void TitleLevel::Update(float _DeltaTime)
{
	// 타이틀레벨에서는 ENTER 키를 입력하면 SelectStage 로 Level 전환
	if (true == GameEngineInput::IsDown("Change_Level"))
	{
		// 현재메뉴를 받아오고. 
		ETitleMenu Menu = m_TitleUI->GetCurMenuType();

		// 메뉴 타입에 따라서 분기처리 
		switch (Menu)

		{
		case ETitleMenu::GAMESTART:
			GameEngineCore::GetInst()->ChangeLevel("SelectLevel");
			break;
		case ETitleMenu::CONTINUE:
			break;
		case ETitleMenu::OPTION:
			break;
		}
	}
}
