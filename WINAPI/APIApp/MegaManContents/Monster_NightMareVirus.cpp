#include "Monster_NightMareVirus.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

Monster_NightMareVirus::Monster_NightMareVirus()
{
}

Monster_NightMareVirus::~Monster_NightMareVirus()
{
}

// 나이트메어바이러스가 생성되면 해야할 일
void Monster_NightMareVirus::Start()
{	
	SetPos({ 600, 600 });
}

// 나이트메어 바이러스 클래스의 내부 연산
void Monster_NightMareVirus::Update()
{
}

// 연산을 토대로 화면에 어떻게 출력할 것인지. 
// 현재 시점을 기준으로 위치를 받아오고.
// 그 위치를 기준으로 가로 80, 세로 80 크기로 사각형을 그린다. 
void Monster_NightMareVirus::Render()
{
	float4 MonsterPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_NightMare_Virus_Left.bmp");
	GameEngineWindow::GetBackBufferImage()->BitCopy(Image, MonsterPos - float4{ 50, 50 }, { 200, 200 });
}
