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
	// �÷��̾��� ��ġ

	// Ű����
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		// �ƽ�Ű�ڵ� 
		// ����Ű ���� 37
		// ����Ű ������ 39
		// ����Ű �Ʒ� 40
		// ����Ű �� 38 
		GameEngineInput::CreateKey("Left", 37);
		GameEngineInput::CreateKey("Right", 39);
		GameEngineInput::CreateKey("Up", 38);
		GameEngineInput::CreateKey("Down", 40);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
	}

	SetPos({ 300, 600 });
	// �������� , ������ ����� �̹���, Zorder �� �Է�
	GameEngineRender* Render = CreateRender("player_recall.bmp", RENDERORDER::PLAYER);
	// �������� x�� y���� ũ�⼳��
	// 165, 200 <-- ����������� �� ��ȣ�� 
	Render->SetScale({ 165, 200 });
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
	// ������
}
