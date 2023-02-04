#include "Monster_GunMan.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

float Monster_GunMan::Time = 0.0f;
Monster_GunMan::Monster_GunMan() :
	m_Render(nullptr)
{
}

Monster_GunMan::~Monster_GunMan()
{
}

void Monster_GunMan::Start()
{
	
	m_Dir = float4::Left;

	// �������� , ������ ����� �̹���, Zorder �� �Է�
	m_Render = CreateRender(ZORDER::MONSTER);
	// �������� x�� y���� ũ�⼳��
	m_Render->SetScale({ 320 * 4.0f , 240 * 4.2f });

	// �浹ü���� , �׷�����
	m_Collision = CreateCollision(COLORDER::MONSTER);
	m_Collision->SetScale({ 100 , 100 });

	m_Render->CreateAnimation({ .AnimationName = "Gunman_idle_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Shot_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Move_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.08f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_throw_Left" , .ImageName = "spaceport_gunman_left.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_Render->CreateAnimation({ .AnimationName = "Gunman_idle_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 1 , .End = 7 , .InterTime = 0.16f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Shot_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 8 , .End = 11 , .InterTime = 0.15f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_Move_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 12 , .End = 18 , .InterTime = 0.1f });
	m_Render->CreateAnimation({ .AnimationName = "Gunman_throw_Right" , .ImageName = "spaceport_gunman_right.bmp" ,
								.Start = 19 , .End = 25 , .InterTime = 0.1f });

	m_Render->ChangeAnimation("Gunman_idle_Left");
	
}

void Monster_GunMan::Update(float _DeltaTime)
{
	// ���� �浹üũ 
	if (true == m_Collision->Collision({ .TargetGroup = static_cast<int>(COLORDER::PLAYER) }))
	{
		this->Death();
	}
	

	// �浹�� �ڵ� �����
	//if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Player) }))
	//{
	//	int a = 0;
	//}

	//std::vector<GameEngineCollision*> Collision;
	//if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Player) }, Collision))
	//{
	//	for (size_t i = 0; i < Collision.size(); i++)
	//	{
	//		// Monster* FindMonster = Collision[i]->GetOwner<Monster>();

	//		GameEngineActor* ColActor = Collision[i]->GetActor();


	//		int a = 0;
	//	}
	//}
}

void Monster_GunMan::Render(float _DeltaTime)
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
