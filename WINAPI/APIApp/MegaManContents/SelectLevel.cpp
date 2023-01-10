#include "SelectLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>

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
	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");

	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
}

void SelectLevel::Update()
{
}
