#include "Monster_MetalT.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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
	Rectangle(GameEngineWindow::GetDrawHdc(),
		MonsterPos.ix() - 20,
		MonsterPos.iy() - 20,
		MonsterPos.ix() + 20,
		MonsterPos.iy() + 20);
}
