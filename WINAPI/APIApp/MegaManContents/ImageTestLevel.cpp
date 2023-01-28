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
	// ���������� �ش� ���͸� ���翩�� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// ��μ���
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("TestImage");


	CreateActor<Monster_GunMan>();
}

void ImageTestLevel::Update(float _DeltaTime)
{
}
