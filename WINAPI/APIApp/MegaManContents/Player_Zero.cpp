#include "Player_Zero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnum.h"

float Player_Zero::Time = 0.0f;

Player_Zero::Player_Zero()
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
		// 아스키코드 
		// 방향키 왼쪽 37
		// 방향키 오른쪽 39
		// 방향키 아래 40
		// 방향키 위 38 
		GameEngineInput::CreateKey("Left", 37);
		GameEngineInput::CreateKey("Right", 39);
		GameEngineInput::CreateKey("Up", 38);
		GameEngineInput::CreateKey("Down", 40);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
	}

	SetPos({ 300, 600 });
	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	GameEngineRender* Render = CreateRender("player_recall.bmp", RENDERORDER::PLAYER);
	// 렌더링시 x축 y축의 크기설정
	// 165, 200 <-- 현재까지봤을 때 양호함 
	Render->SetScale({ 165, 200 });
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
