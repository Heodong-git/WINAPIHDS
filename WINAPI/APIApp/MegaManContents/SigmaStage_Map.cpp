#include "SigmaStage_Map.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

SigmaStage_Map::SigmaStage_Map()
{
}

SigmaStage_Map::~SigmaStage_Map()
{
}

void SigmaStage_Map::Start()
{
	// �ϴ� ����������Ʈ ������ �ٽ� 
	{
		GameEngineRender* AnimationRender = CreateRender(RENDERORDER::MAP);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4 { 10000 , - 4000});
		AnimationRender->SetImage("Sigma_Stage.Bmp");
		AnimationRender->SetScale({ AnimationRender->GetImage()->GetImageScale()});
		
	}
}
