#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

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
	// ���߿� ���ȭ�� ������ �� �ٽ� �غ� �� 
	//GameEngineDirectory Directory;
	//// ���������� �ش� ���͸��� �ִ��� Ȯ��
	//Directory.MoveParentToDirectory("ContentsResources");

	//// ���͸��� �ִٸ� ��θ� �������ش�.  
	//Directory.Move("ContentsResources");
	//Directory.Move("Image");

	//GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));
}

void TitleLevel::Update()
{

}
