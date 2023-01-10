#include "Monster_MetalT.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>


int Monster_MetalT::Time = 0;
Monster_MetalT::Monster_MetalT()
{
}

Monster_MetalT::~Monster_MetalT()
{
}

void Monster_MetalT::Start()
{
	SetPos({ 800, 300 });
	Dir = float4::Left;
}

void Monster_MetalT::Update()
{
	++Time;
	if (1000 >= Time)
	{
		SetMove(float4::Left * 0.1f);
	}

	else if (1000 < Time)
	{
		SetMove(float4::Right * 0.1f);
	}

	if (2000 <= Time)
	{
		Time = 0;
	}
}

void Monster_MetalT::Render()
{
	float4 MonsterPos = GetPos();

	// 이미지를 찾는다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_Metal_T_Left.bmp");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos - float4{ 50, 50 }, { 100, 100 }, { 446, 14 }, {80, 93});
	
}
