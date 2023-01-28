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
	PlayerState PrevState = m_StateValue;
	// ���� ���¸� ����� ���·� �����Ѵ�. 
	m_StateValue = NextState;

	switch (NextState)
	{
	case PlayerState::RECALL:
		RecallStart();
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
	default:
		break;
	}

	// ����� ���¿� ���� �� ������ End �Լ��� ȣ��
	switch (PrevState)
	{
	case PlayerState::RECALL:
		RecallEnd();
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
	default:
		break;
	}
}

// ���¾�����Ʈ 
void Player_Zero::UpdateState(float _Time)
{
	// ���� ���°��� ���� �б�ó��
	switch (m_StateValue)
	{
	case PlayerState::RECALL:
		RecallUpdate(_Time);
		break;
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
	default:
		break;
	}

}

void Player_Zero::RecallStart()
{
}

void Player_Zero::RecallUpdate(float _DeltaTime)
{
	if (18 == m_AnimationRender->GetFrame())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// �ִϸ��̼� �����߿� ����, ������Ű�� ������ �ƹ��͵� �������� �ʵ��� ����ó��
	if (true == GameEngineInput::IsPress("LeftMove") || true == GameEngineInput::IsPress("RightMove"))
	{
		return;
	}
	// ������ ������Ʈ������ �ִϸ��̼� ����� �Ϸ� �ƴٸ� ���̵� ���·� ��ȯ�Ѵ�. 
	// ����Ϸ� ������ �������� Ȯ���Ͽ� ������ �����ӿ� �����ߴٸ� , ���̵�� ��ȯ
	// ��.. �ٵ� �� ���ݽ�ŸƮ���� �ִϸ��̼� ������ �ȵ��� , �ڵ��ľ� ���� �ʿ� 
	DirCheck("recall");
}

void Player_Zero::RecallEnd()
{
}

void Player_Zero::IdleStart()
{
	DirCheck("Idle");
}

void Player_Zero::IdleUpdate(float _Time)
{

	// Idle ������ ��� ����, ������ Ű�� ���ȴٸ� Move ���·� �����Ѵ�.  
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
		return;
	}

	if (GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::NOMALATTACK);
		return;
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
		if (true == GameEngineInput::IsPress("LeftMove") && true == GameEngineInput::IsPress("RightMove"))
		{
			return;
		}
		m_MoveDir += float4::Left * m_MoveSpeed;
		//GetLevel()->SetCameraMove(float4::Left * _Time * MoveSpeed);
	}
	
	if (true == GameEngineInput::IsPress("RightMove"))
	{
		if (true == GameEngineInput::IsPress("LeftMove") && true == GameEngineInput::IsPress("RightMove"))
		{
			return;
		}
		m_MoveDir += float4::Right * m_MoveSpeed;
		//GetLevel()->SetCameraMove(float4::Right * _Time * MoveSpeed);
	}

	if (GameEngineInput::IsPress("Attack"))
	{
		ChangeState(PlayerState::NOMALATTACK);
		return;
	}

	DirCheck("Move");
}



void Player_Zero::MoveEnd()
{
}

// �Ϲݰ��� 
void Player_Zero::NormalAttackStart()
{
	DirCheck("normal_attack");
}

void Player_Zero::NormalAttackUpdate(float _Time)
{
	// ������ ������ �����ӿ� �����ϸ� Idle ���·� �������ش�. 
	// �ϴ� �ӽ÷� �����صΰ�, ���߿� ���鶧 �븻���� 1Ÿ, 23Ÿ ���·� �����ؼ� �����Ѵ�. 
	if (28 == m_AnimationRender->GetFrame())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player_Zero::NormalAttackEnd()
{
}

void Player_Zero::DashStart()
{
	DirCheck("Dash");
}

void Player_Zero::DashUpdate(float _Time)
{



	DirCheck("Dash");
}

void Player_Zero::DashEnd()
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

void Player_Zero::FallStart()
{
}

void Player_Zero::FallUpdate(float _DeltaTime)
{
}

void Player_Zero::FallEnd()
{
}


