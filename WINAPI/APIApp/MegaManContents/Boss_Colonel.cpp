#include "Boss_Colonel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

Boss_Colonel::Boss_Colonel()
{
}

Boss_Colonel::~Boss_Colonel()
{
}

void Boss_Colonel::Start()
{
	m_Render = CreateRender(ZORDER::BOSS);
	m_Render->SetScale({ 640 * 1.7f , 480 * 2.0f });

	AnimationCreate();

	m_Render->ChangeAnimation("Colonel_Start_left");
}

void Boss_Colonel::Update(float _DeltaTime)
{
}

void Boss_Colonel::Render(float _DeltaTime)
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

void Boss_Colonel::AnimationCreate()
{
	// �������۸��
	m_Render->CreateAnimation({ .AnimationName = "Colonel_Start_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });
	// �⺻�ڼ� 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_idle_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 2 , .End = 3 , .InterTime = 0.2f });
	// �ڷ���Ʈ left 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_TeleportAttack_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 4 , .End = 9 , .InterTime = 0.14f , .Loop = false });
	// �ʽ´޴�����? ������� �ٽ� 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_Moonthrow_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 9 , .End = 10 , .InterTime = 0.8f });

	
}
