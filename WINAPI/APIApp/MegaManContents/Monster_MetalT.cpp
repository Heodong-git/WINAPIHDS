#include "Monster_MetalT.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

float Monster_MetalT::Time = 0.0f;
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

	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	GameEngineRender* Render = CreateRender("monster_metal_t_left.bmp", RENDERORDER::MONSTER);
	// 렌더링시 x축 y축의 크기설정
	Render->SetScale({ 100, 100 });
	
}

void Monster_MetalT::Update(float _DeltaTime)
{
	Time += _DeltaTime;
	if (4 >= Time)
	{
		SetMove(float4::Left * 100.0f * _DeltaTime);
	}

	else if (4 < Time)
	{
		SetMove(float4::Right * 100.0f * _DeltaTime);
	}

	if (9 <= Time)
	{
		Time -= Time;
	}
}

void Monster_MetalT::Render(float _DeltaTime)
{
	//float4 MonsterPos = GetPos();

	//// 이미지를 찾는다. 
	//GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_Metal_T_Left.bmp");

	//GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 100, 100 }, { 446, 14 }, {80, 93});
}
