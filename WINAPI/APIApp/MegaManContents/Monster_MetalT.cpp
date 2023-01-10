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

	// �̹����� ã�´�. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_Metal_T_Left.bmp");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos - float4{ 50, 50 }, { 100, 100 }, { 446, 14 }, {80, 93});
	
}
