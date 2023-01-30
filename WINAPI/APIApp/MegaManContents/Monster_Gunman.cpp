#include "Monster_GunMan.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
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
	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	m_Render = CreateRender(RENDERORDER::MONSTER);
	// 렌더링시 x축 y축의 크기설정
	m_Render->SetScale({ 320 * 4.0f , 240 * 4.2f });
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

void Monster_GunMan::Render(float _DeltaTime)
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
