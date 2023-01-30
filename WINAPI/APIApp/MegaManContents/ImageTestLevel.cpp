#include "ImageTestLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Boss_Colonel.h"
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

	// gunman image
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_left.bmp"));
		Image->Cut(8, 5);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_right.bmp"));
		Image->Cut(8, 5);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_colonel_left.bmp"));
		Image->Cut(8, 6);
	}

	GameEngineActor* Monster = CreateActor<Monster_GunMan>();
	GameEngineActor* Boss = CreateActor<Boss_Colonel>();
}

void ImageTestLevel::Update(float _DeltaTime)
{
}
