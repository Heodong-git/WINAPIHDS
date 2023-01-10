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

// 타이틀레벨의 로딩에서 필요한 것?
// 1. UI
// 2. 배경화면
// 3. Sound ?
void TitleLevel::Loading()
{
	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");

	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");

	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Main_Title.bmp"));
}

void TitleLevel::Update()
{

}
