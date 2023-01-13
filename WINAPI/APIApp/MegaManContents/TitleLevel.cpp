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

// Ÿ��Ʋ������ �ε����� �ʿ��� ��?
// 1. UI
// 2. ���ȭ��
// 3. Sound ?
void TitleLevel::Loading()
{
	// ENTER <-- ���� 13
	GameEngineInput::CreateKey("Change_SelectLevel", 13);
	GameEngineDirectory Directory;
	// ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");

	// ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("Title");

	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));

	CreateActor<Title_BackGround>();
}

void TitleLevel::Update(float _DeltaTime)
{
	// Ÿ��Ʋ���������� ENTER Ű�� �Է��ϸ� SelectStage �� Level ��ȯ
	if (true == GameEngineInput::IsDown("Change_SelectLevel"))
	{
		GameEngineCore::GetInst()->ChangeLevel("SelectLevel");
	}
}
