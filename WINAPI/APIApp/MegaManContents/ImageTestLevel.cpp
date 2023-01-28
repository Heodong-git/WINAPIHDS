#include "ImageTestLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Monster_Gunman.h"

ImageTestLevel::ImageTestLevel()
{
}

ImageTestLevel::~ImageTestLevel()
{
}

void ImageTestLevel::Loading()
{
	GameEngineDirectory Directory;
	// 상위폴더에 해당 디렉터리 존재여부 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 경로설정
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("TestImage");


	CreateActor<Monster_GunMan>();
}

void ImageTestLevel::Update(float _DeltaTime)
{
}
