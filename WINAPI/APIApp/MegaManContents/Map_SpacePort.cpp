#include "Map_SpacePort.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Map_SpacePort::Map_SpacePort()
{
}

Map_SpacePort::~Map_SpacePort()
{
}

void Map_SpacePort::Start()
{
	// 일단 엔진업데이트 끝나고 다시 
	{
		GameEngineRender* AnimationRender = CreateRender(ZORDER::MAP);
		AnimationRender->SetImage("Map_SpacePort.Bmp");
		AnimationRender->SetPosition(AnimationRender->GetImage()->GetImageScale().half());
		AnimationRender->SetScaleToImage();
	}
}
