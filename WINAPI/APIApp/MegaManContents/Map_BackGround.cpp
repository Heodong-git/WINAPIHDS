#include "Map_BackGround.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

Map_BackGround::Map_BackGround()
{
}

Map_BackGround::~Map_BackGround()
{
}

void Map_BackGround::Start()
{
	SetPos(GameEngineWindow::GetScreenSize().half());
}

void Map_BackGround::Update()
{
}

void Map_BackGround::Render()
{
	float4 MapPos = GetPos();

	// 1. 이미지를 찾는다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Sigma_Stage.bmp");

	// 2.  현재 백버퍼의 이미지의 TransCopy 함수를 호출하여
	// 백버퍼의  특정 위치에 플레이어의 이미지를 복사한다. 
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MapPos, { 1360, 768 },
														float4{ 6 , 1285 }, { 511, 254 });
}
