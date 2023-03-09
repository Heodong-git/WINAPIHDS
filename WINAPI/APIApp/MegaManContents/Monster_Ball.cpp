#include "Monster_Ball.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

float Monster_Ball::Time = 0.0f;

Monster_Ball::Monster_Ball() :
	AnimationRender(nullptr)
{
}

Monster_Ball::~Monster_Ball()
{
}

// ����Ʈ�޾���̷����� �����Ǹ� �ؾ��� ��
void Monster_Ball::Start()
{
	AnimationRender = CreateRender(ZORDER::MONSTER);
	AnimationRender->SetScale({200, 200});

	AnimationRender->CreateAnimation({ .AnimationName = "ball_move" , .ImageName = "monster_ball.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.8f });
	AnimationRender->ChangeAnimation("ball_move");

}

// ����Ʈ�޾� ���̷��� Ŭ������ ���� ����
void Monster_Ball::Update(float _DeltaTime)
{
	/*Time += _DeltaTime;
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
	}*/
}

// ������ ���� ȭ�鿡 ��� ����� ������. 
// ���� ������ �������� ��ġ�� �޾ƿ���.
// �� ��ġ�� �������� ���� 80, ���� 80 ũ��� �簢���� �׸���. 
void Monster_Ball::Render(float _DeltaTime)
{
	/*float4 MonsterPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_NightMare_Virus_Left.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 100, 100 }, {60, 0}, { 140, 140 });*/
}
