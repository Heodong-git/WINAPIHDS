#include "Player_Zero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnum.h"

float Player_Zero::Time = 0.0f;

Player_Zero::Player_Zero() :
	AnimationRender(nullptr)
{
}

Player_Zero::~Player_Zero()
{
}

// 방향체크
void Player_Zero::DirCheck()
{
	// 현재 Left 키가 눌렸다면 
	if (GameEngineInput::IsPress("LeftMove"))
	{
		// 방향문자열을 Left_
		Dir = "Left_";
	}
	else if (GameEngineInput::IsPress("RightMove"))
	{
		Dir = "Right_";
	}
}

void Player_Zero::Start()
{
	// 플레이어의 위치

	// 키생성
	// 문자열을 키값으로 하여 원하는 키와 
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
		GameEngineInput::CreateKey("UpMove", VK_UP);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
	}

	// 플레이어 크기 165 , 200 
	SetPos({ 300, 600 });
	
	// 렌더러생성, 생성시 zorder 값 입력 
	AnimationRender = CreateRender(RENDERORDER::PLAYER);
	AnimationRender->SetScale({ 250,250 });

	// 구조체를 넣어주는데 원하는 변수의 값만 수정하여 넣어줄 수 있다.
	// 단, 순서는 지켜서 넣어주어야 빨간줄이 그이지 않는다. 

	// 우측 
	AnimationRender->CreateAnimation({ .AnimationName = "right_idle",  .ImageName = "player_idle_walk_right.bmp", 
									   .Start = 0, .End = 5 , .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "right_move_start",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "right_move",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });

	// 좌측
	AnimationRender->CreateAnimation({ .AnimationName = "left_idle",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "left_move_start",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.1f });
	AnimationRender->CreateAnimation({ .AnimationName = "left_move",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });

	ChangeState(PlayerState::IDLE);
}

void Player_Zero::Update(float _DeltaTime)
{
	DirCheck();
	// 현재 플레이어의 상태값에 따라 업데이트를 진행.
	UpdateState(_DeltaTime);
}

// 오브젝트의 중심점을 알 수 있도록 사각형 출력 
void Player_Zero::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

}
