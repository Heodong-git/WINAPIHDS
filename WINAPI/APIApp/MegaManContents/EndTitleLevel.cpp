#include "EndTitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>

EndTitleLevel::EndTitleLevel()
{
}

EndTitleLevel::~EndTitleLevel()
{
}

// 
void EndTitleLevel::Loading()
{
	// 이미지로딩
	// 디렉터리 객체생성 , 디렉터리는 경로를 가지고 있음.
	GameEngineDirectory Directory;

	// 1. 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
}

void EndTitleLevel::Update(float _DeltaTime)
{
}
