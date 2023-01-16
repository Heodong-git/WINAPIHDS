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

void Player_Zero::Start()
{
	// 플레이어의 위치

	// 키생성
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("Left", VK_LEFT);
		GameEngineInput::CreateKey("Right", VK_RIGHT);
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
	}

	// 플레이어 크기 165 , 200 
	SetPos({ 300, 600 });
	
	// 렌더러생성, 생성시 zorder 값 입력 
	AnimationRender = CreateRender(RENDERORDER::PLAYER);
	AnimationRender->SetScale({ 165,200 });
	
	// 구조체를 넣어주는데 원하는 변수의 값만 수정하여 넣어줄 수 있음
	// 단, 순서는 지켜서 넣어주어야 빨간줄이 그이지 않는다. 
	AnimationRender->CreateAnimation({ .AnimationName = "player_recall",  .ImageName = "player_recall.bmp", .Start = 0, .End = 8 });
	AnimationRender->ChangeAnimation("player_recall");
	
}

// 플레이어 연산
void Player_Zero::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("Left"))
	{
		SetMove(float4::Left * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("Right"))
	{
		SetMove(float4::Right * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("Up"))
	{
		SetMove(float4::Up * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("Down"))
	{
		SetMove(float4::Down * MoveSpeed * _DeltaTime);
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		int a = 0;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		SetMove(float4{ 0 , -200 } *MoveSpeed * _DeltaTime);
	}
}

void Player_Zero::Render(float _DeltaTime)
{
	// 디버깅용
}
