#include "Monster_Ball.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpacePortLevel.h"
#include "Player_Zero.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"
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
	AnimationRender->SetScale({400, 400});

	AnimationRender->CreateAnimation({ .AnimationName = "ball_move" , .ImageName = "monster_ball.bmp" ,
								.Start = 0 , .End = 2 , .InterTime = 0.03f });
	AnimationRender->ChangeAnimation("ball_move");

	m_Collider = CreateCollision(COLORDER::MONSTER);
	m_Collider->SetScale(float4{ 150, 150 });
}

// ����Ʈ�޾� ���̷��� Ŭ������ ���� ����
void Monster_Ball::Update(float _DeltaTime)
{
	SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
	if (nullptr != Level)
	{
		float4 PlayerPos = Level->GetPlayer()->GetPos();
		float4 MovePos = PlayerPos - GetPos();
		MovePos.Normalize();
		float Range = GetPos().x - PlayerPos.x;
		
		if (Range <= m_Range)
		{
			SetMove(MovePos * m_MoveSpeed * _DeltaTime);

			
		}
	}

	// ���� �浹üũ 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// ���⼭ ����Ʈ �����Ÿ� ���
		Effect_Hit* Hit_Effect = GetLevel()->CreateActor<Effect_Hit>();
		Hit_Effect->SetPos(GetPos() + float4{ -30, -100 });

		this->Death();

		m_Sound = GameEngineResources::GetInst().SoundPlayToControl("fire.wav");
		m_Sound.LoopCount(1);
		m_Sound.Volume(0.2f);

		Effect_Explosion* E_Effect = GetLevel()->CreateActor<Effect_Explosion>();
		E_Effect->SetPos(GetPos());

	}

	// �浹�� �ڵ� �����
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) }))
	{
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
		if (nullptr != Level)
		{
			Player_Zero* Player = Level->GetPlayer();
			float4 PlayerPos = Player->GetPos();
			float Range = GetPos().x - PlayerPos.x;

			if (Range > 0.0f)
			{
				Player->ChangeState(STATEVALUE::BIGHIT);
				Player->Damage(2);
				Effect_Explosion* Effect = GetLevel()->CreateActor<Effect_Explosion>(ZORDER::EFFECT);
				Effect->SetPos(GetPos());
				this->Death();
				return;
			}

			else if (Range <= 0.0f)
			{
				Player->ChangeState(STATEVALUE::BIGHIT);
				Player->Damage(2);
				Effect_Explosion* Effect = GetLevel()->CreateActor<Effect_Explosion>(ZORDER::EFFECT);
				Effect->SetPos(GetPos());
				this->Death();
				return;
			}
		}
	}

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
	// ������
	/*HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);*/
}
