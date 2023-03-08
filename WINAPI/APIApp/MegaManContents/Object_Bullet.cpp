#include "Object_Bullet.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "SpacePortLevel.h"
#include "Player_Zero.h"
#include "ContentsEnum.h"
#include "Effect_Hit.h"
#include "Effect_Explosion.h"

Object_Bullet::Object_Bullet()
{
}

Object_Bullet::~Object_Bullet()
{
}

void Object_Bullet::Start()
{
	// �ִϸ��̼� ���� ����
	m_AnimationRender = CreateRender(ZORDER::OBJECT);
	m_AnimationRender->SetScale(float4{ 50, 50 });

	// �Ѿ˾ִϸ��̼� �����ؾ���.
	m_AnimationRender->CreateAnimation({ .AnimationName = "bullet_fire" , .ImageName = "gunman_bullet.bmp",
									   .Start = 0 , .End = 3 , .InterTime = 0.05f });

	m_AnimationRender->ChangeAnimation("bullet_fire");

	// �浹ü ����
	m_Collider = CreateCollision(COLORDER::OBJECT_BULLET);
	m_Collider->SetScale({ 50, 50 });
}

void Object_Bullet::Update(float _DeltaTime)
{
	m_LiveTime -= _DeltaTime;
	if (m_LiveTime <= 0.0f)
	{
		this->Death();
	}

	// ���� �浹üũ 
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYERATTACK) }))
	{
		// ���⼭ ����Ʈ �����Ÿ� ���
		Effect_Hit* Hit_Effect = GetLevel()->CreateActor<Effect_Hit>();
		Hit_Effect->SetPos(GetPos());

		m_Sound = GameEngineResources::GetInst().SoundPlayToControl("fire.wav");
		m_Sound.LoopCount(1);
		m_Sound.Volume(0.2f);

		this->Death();

		Effect_Explosion* E_Effect = GetLevel()->CreateActor<Effect_Explosion>();
		E_Effect->SetPos(GetPos());

		return;
	}

	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) }))
	{
		SpacePortLevel* Level = dynamic_cast<SpacePortLevel*>(GetLevel());
		// �����ȿ� ���Դٸ� shot state�� �����ε�.. ��
		if (nullptr != Level)
		{
			Level->GetPlayer()->Damage(m_Damage);
			Level->GetPlayer()->ChangeState(STATEVALUE::HIT);
		}
		this->Death();
		return;
	}

	SetMove(m_MoveDir * m_MoveSpeed * _DeltaTime);
}

void Object_Bullet::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
