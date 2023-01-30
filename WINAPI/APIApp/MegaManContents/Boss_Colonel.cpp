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
	m_Render = CreateRender(RENDERORDER::MONSTER);
	m_Render->SetScale({ 640 * 1.7f , 480 * 2.0f });

	// 전투시작모션
	m_Render->CreateAnimation({ .AnimationName = "Colonel_Start_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 0 , .End = 4 , .InterTime = 0.15f });
	// 기본자세 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_idle_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 2 , .End = 3 , .InterTime = 0.2f });
	// 텔레포트 left 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_TeleportAttack_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 4 , .End = 9 , .InterTime = 0.14f , .Loop = false} );
	// 초승달던지기? 여기부터 다시 
	m_Render->CreateAnimation({ .AnimationName = "Colonel_Moonthrow_Left" , .ImageName = "spaceport_colonel_left.bmp" ,
								.Start = 9 , .End = 10 , .InterTime = 0.8f });

	m_Render->ChangeAnimation("Colonel_TeleportAttack_left");
	
}

void Boss_Colonel::Update(float _DeltaTime)
{
}

void Boss_Colonel::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

}
