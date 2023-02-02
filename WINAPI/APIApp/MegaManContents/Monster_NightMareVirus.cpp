#include "Monster_NightMareVirus.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

float Monster_NightMareVirus::Time = 0.0f;

Monster_NightMareVirus::Monster_NightMareVirus() :
	AnimationRender(nullptr)
{
}

Monster_NightMareVirus::~Monster_NightMareVirus()
{
}

// ����Ʈ�޾���̷����� �����Ǹ� �ؾ��� ��
void Monster_NightMareVirus::Start()
{
	SetPos({ 600, 600 });

	AnimationRender = CreateRender(ZORDER::MONSTER);
	AnimationRender->SetScale({200, 200});
	AnimationRender->CreateAnimation({ .AnimationName = "monster_nightmare_virus_leftidle",
									  .ImageName = "monster_nightmare_virus_left.bmp",
									  .Start = 0 , .End = 2 });
	AnimationRender->ChangeAnimation("monster_nightmare_virus_leftidle");
}

// ����Ʈ�޾� ���̷��� Ŭ������ ���� ����
void Monster_NightMareVirus::Update(float _DeltaTime)
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

// ������ ���� ȭ�鿡 ��� ����� ������. 
// ���� ������ �������� ��ġ�� �޾ƿ���.
// �� ��ġ�� �������� ���� 80, ���� 80 ũ��� �簢���� �׸���. 
void Monster_NightMareVirus::Render(float _DeltaTime)
{
	/*float4 MonsterPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_NightMare_Virus_Left.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 100, 100 }, {60, 0}, { 140, 140 });*/
}
