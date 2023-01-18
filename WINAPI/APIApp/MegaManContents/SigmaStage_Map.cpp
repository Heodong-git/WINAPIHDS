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
	// 일단 엔진업데이트 끝나고 다시 
	{
		GameEngineRender* AnimationRender = CreateRender(RENDERORDER::MAP);
		AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4 { 10000 , - 4000});
		AnimationRender->SetImage("Sigma_Stage.Bmp");
		AnimationRender->SetScale({ AnimationRender->GetImage()->GetImageScale()});
		
	}
}
