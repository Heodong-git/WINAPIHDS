#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"


// ���º��� �Լ�
void Player_Zero::ChangeState(PlayerState _State)
{
	// �÷��̾��� ���� ���¸� �޾ƿ´�. 
	PlayerState NextState = _State;
	// �÷��̾��� ���� ���´� ���� ���°� �ȴ�. 
	PlayerState PrevState = StateValue;
	// ���� ���¸� ����� ���·� �����Ѵ�. 
	StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::IDLE:
		IdleStart();
		break;
	case PlayerState::MOVE:
		MoveStart();
		break;
	case PlayerState::JUMP:
		JumpStart();
		break;
	case PlayerState::DASH:
		DashStart();
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackStart();
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackStart();
		break;
	case PlayerState::DASHATTACK:
		DashAttackStart();
	default:
		break;
	}

	// ����� ���¿� ���� �� ������ End �Լ��� ȣ��
	switch (PrevState)
	{
	case PlayerState::IDLE:
		IdleEnd();
		break;
	case PlayerState::MOVE:
		MoveEnd();
		break;
	case PlayerState::JUMP:
		JumpEnd();
		break;
	case PlayerState::DASH:
		DashEnd();
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackEnd();
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackEnd();
		break;
	case PlayerState::DASHATTACK:
		DashAttackEnd();
	default:
		break;
	}
}

// ���¾�����Ʈ 
void Player_Zero::UpdateState(float _Time)
{
	// ���� ���°��� ���� �б�ó��
	switch (StateValue)
	{
	case PlayerState::IDLE:
		IdleUpdate(_Time);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_Time);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_Time);
		break;
	case PlayerState::DASH:
		DashUpdate(_Time);
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackUpdate(_Time);
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackUpdate(_Time);
		break;
	case PlayerState::DASHATTACK:
		DashAttackUpdate(_Time);
	default:
		break;
	}

}

void Player_Zero::IdleStart()
{
	DirCheck("Idle");
}

void Player_Zero::IdleUpdate(float _Time)
{
	// �⺻ ������ ������Ʈ������ Ư��Ű�� ������ 
	// ���ϴ� ���¿� �°� ���¸� �������ش�. 
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove")
		|| GameEngineInput::IsPress("UpMove") || GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // ���� ������Ʈ�� ü�����ϸ� �Ʒ� �ڵ带 ����Ǹ� 
	}
}

void Player_Zero::IdleEnd()
{
}

void Player_Zero::MoveStart()
{
	DirCheck("Move");
}

void Player_Zero::MoveUpdate(float _Time)
{	
	// ������ ������Ʈ������ ���� �ƹ�Ű�� ������ �ʾҴٸ� �⺻ IDLE ���·� �����Ѵ�.  
	if (
		false == GameEngineInput::IsPress("LeftMove") &&
		false == GameEngineInput::IsPress("RightMove") &&
		false == GameEngineInput::IsPress("UpMove") &&
		false == GameEngineInput::IsPress("DownMove")
		)
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// Ű�� ���ȴٸ� �ش��ϴ� ������ ����
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		//AnimationRender->ChangeAnimation(DirString + "Move");
		SetMove(float4::Left * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Left * _Time * MoveSpeed);
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		//AnimationRender->ChangeAnimation(DirString +"Move");
		SetMove(float4::Right * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Right * _Time * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		SetMove(float4::Up * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Up * _Time * MoveSpeed);
	}

	else if (true == GameEngineInput::IsPress("DownMove"))
	{
		//AnimationRender->ChangeAnimation(DirString +"Move");
		SetMove(float4::Down * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Down * _Time * MoveSpeed);
	}

	// ���ʹ��긦 ����üũ�ϱ� ������ ������Ű�� �������¿����� ����Ű�� ������ 
	// if ���� �����Ͽ� �ݴ�� �̵� + �ִϸ��̼���  ��µ����� ����Ű�� �������¿�����
	// ������Ű�� ������ ���ʹ���üũ�� �����Ǿ� �Ʒ� �ڵ尡 �������� �ʴ� �� ����. 

	DirCheck("Move");
}

void Player_Zero::MoveEnd()
{
}

void Player_Zero::NormalAttackStart()
{
}

void Player_Zero::NormalAttackUpdate(float _Time)
{
}

void Player_Zero::NormalAttackEnd()
{
}

void Player_Zero::JumpStart()
{
}

void Player_Zero::JumpUpdate(float _Time)
{
}

void Player_Zero::JumpEnd()
{
}

void Player_Zero::JumpAttackStart()
{
}

void Player_Zero::JumpAttackUpdate(float _Time)
{
}

void Player_Zero::JumpAttackEnd()
{
}

void Player_Zero::DashStart()
{
}

void Player_Zero::DashUpdate(float _Time)
{
}

void Player_Zero::DashEnd()
{
}

void Player_Zero::DashAttackStart()
{
}

void Player_Zero::DashAttackUpdate(float _Time)
{
}

void Player_Zero::DashAttackEnd()
{
}
