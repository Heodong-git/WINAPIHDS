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
	// �÷��̾��� ��ġ

	// Ű����
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

	// �÷��̾� ũ�� 165 , 200 
	SetPos({ 300, 600 });
	
	// ����������, ������ zorder �� �Է� 
	AnimationRender = CreateRender(RENDERORDER::PLAYER);
	AnimationRender->SetScale({ 165,200 });
	
	// ����ü�� �־��ִµ� ���ϴ� ������ ���� �����Ͽ� �־��� �� �ִ�.
	// ��, ������ ���Ѽ� �־��־�� �������� ������ �ʴ´�. 
	AnimationRender->CreateAnimation({ .AnimationName = "player_recall",  .ImageName = "player_recall.bmp", .Start = 0, .End = 0 });
	AnimationRender->ChangeAnimation("player_recall");
	
}

// �÷��̾� ����
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
		// �뽬 ��ư�� ������ �� ������ �ִϸ��̼ǰ� ����
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		// ���� ��ư�� ������ �� ������ �ִϸ��̼ǰ� ����
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		// ���� ��ư�� ������ �� ������ �ִϸ��̼ǰ� ����
	}
}

void Player_Zero::Render(float _DeltaTime)
{
	// ������
}
