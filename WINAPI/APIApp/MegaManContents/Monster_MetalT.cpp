#include "Monster_MetalT.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

Monster_MetalT::Monster_MetalT()
{
}

Monster_MetalT::~Monster_MetalT()
{
}

void Monster_MetalT::Start()
{
	SetPos({ 800, 300 });
}

void Monster_MetalT::Update()
{
}

void Monster_MetalT::Render()
{
	float4 MonsterPos = GetPos();
	
	// 이미지를 찾는다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_Metal_T_Left.bmp");

	GameEngineWindow::GetBackBufferImage()->BitCopy(Image, MonsterPos - float4{ 50, 50 }, { 200, 200 });
	
}
