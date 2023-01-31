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
	m_NextState = _State;
	// �÷��̾��� ���� ���´� ���� ���°� �ȴ�. 
	m_PrevState = m_StateValue;
	// ���� ���¸� ����� ���·� �����Ѵ�. 
	m_StateValue = m_NextState;

	switch (m_NextState)
	{
	case PlayerState::RECALL:
		RecallStart();
		break;
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
	case PlayerState::SIT:
		SitStart();
		break;
	case PlayerState::SITATTACK:
		SitAttackStart();
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackStart();
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackStart();
		break;
	case PlayerState::DOUBLEJUMP:
		DoubleJumpStart();
		break;
	case PlayerState::HIT:
		break;
	default:
		break;
	}

	// ����� ���¿� ���� �� ������ End �Լ��� ȣ��
	switch (m_PrevState)
	{
	case PlayerState::RECALL:
		RecallEnd();
		break;
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
	case PlayerState::SIT:
		SitEnd();
		break;
	case PlayerState::SITATTACK:
		SitAttackEnd();
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackEnd();
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackEnd();
		break;
	case PlayerState::DOUBLEJUMP:
		DoubleJumpEnd();
		break;
	case PlayerState::HIT:
		HitEnd();
		break;
	default:
		break;
	}
}

// ���¾�����Ʈ 
void Player_Zero::UpdateState(float _DeltaTime)
{
	// ���� ���°��� ���� �б�ó��
	switch (m_StateValue)
	{
	case PlayerState::RECALL:
		RecallUpdate(_DeltaTime);
		break;
	case PlayerState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case PlayerState::MOVE:
		MoveUpdate(_DeltaTime);
		break;
	case PlayerState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case PlayerState::DASH:
		DashUpdate(_DeltaTime);
		break;
	case PlayerState::SIT:
		SitUpdate(_DeltaTime);
		break;
	case PlayerState::SITATTACK:
		SitAttackUpdate(_DeltaTime);
		break;
	case PlayerState::NOMALATTACK:
		NormalAttackUpdate(_DeltaTime);
		break;
	case PlayerState::JUMPATTACK:
		JumpAttackUpdate(_DeltaTime);
		break;
	case PlayerState::DOUBLEJUMP:
		DoubleJumpUpdate(_DeltaTime);
		break;
	case PlayerState::HIT:
		HitUpdate(_DeltaTime);
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
	if (GameEngineInput::IsPress("Sit"))
	{
		ChangeState(PlayerState::SIT);
		return;
	}

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

	if (GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::DASH);
		return;
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
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

void Player_Zero::MoveUpdate(float _DeltaTime)
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

	// ����Ű�� ���ȴٸ� ���� 
	if (GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::NOMALATTACK);
		return;
	}

	if (GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	if (GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::DASH);
		return;
	}

	if (GameEngineInput::IsDown("Sit"))
	{
		ChangeState(PlayerState::SIT);
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
	if (m_AnimationRender->IsAnimationEnd())
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
	// �뽬������Ʈ������ ���߻��¿��� �뽬 ����� ����Ǹ� 
	// ���ϸ������ �ٲ�����. �ᱹ �׳� ���ϸ���� ���� �ؾߵǳ� 
	if (m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
}

void Player_Zero::DashEnd()
{
}

void Player_Zero::HitStart()
{
	DirCheck("player_hit");
}

void Player_Zero::HitUpdate(float _DeltaTime)
{
	// ���� �ĸ´� ���� ���� �°��� �ִϸ��̼��� ������ ������ �����̾����.
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player_Zero::HitEnd()
{
}


void Player_Zero::JumpStart()
{
	DirCheck("Jump");
}

void Player_Zero::JumpUpdate(float _Time)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
	
	if (true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(PlayerState::DOUBLEJUMP);
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::JUMPATTACK);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::DASH);
		return;
	}
	// ����Ű �߿� �ݴ����Ű�� ������ �������� �ִϸ��̼��� �ٲ�����. 
	if (true == GameEngineInput::IsPress("LeftMove") || true == GameEngineInput::IsPress("RightMove"))
	{
		// ��.. ��.. ��.. ����.. �ϴ� ���߿� �ٸ� �ִϸ��̼Ǻ���.. 
		return;
	}
}

void Player_Zero::JumpEnd()
{
	
}

void Player_Zero::JumpAttackStart()
{
	DirCheck("Jump_Attack");
}

void Player_Zero::JumpAttackUpdate(float _DeltaTime)
{
	// ���߿� ���� ������������ �ƴ����� �߰��ؼ� �ٽ� ����
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		
		if (true == GameEngineInput::IsDown("Jump"))
		{
			ChangeState(PlayerState::DOUBLEJUMP);
		}



		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player_Zero::JumpAttackEnd()
{
}

void Player_Zero::DoubleJumpStart()
{
	DirCheck("Double_jump");
}

void Player_Zero::DoubleJumpUpdate(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player_Zero::DoubleJumpEnd()
{
}

void Player_Zero::SitStart()
{
	DirCheck("Sit");
}
void Player_Zero::SitUpdate(float _DeltaTime)
{
	// �ɱ� Ű�� ��� �����־��ٸ�
	if (true == GameEngineInput::IsPress("Sit"))
	{
		// ������ �ɾ��ִ� �ִϸ��̼��� �����ϰ�
		DirCheck("press_sit");

		// ���� ���¿��� ����Ű�� �����ٸ� �������� ���·� �����ε�. 
		if (true == GameEngineInput::IsDown("Attack"))
		{
			ChangeState(PlayerState::SITATTACK);
		}

		return;
	}

	// Ű�� �������� �ʾҴٸ� IDLE ���·� ��ȯ 
	else
	{
		ChangeState(PlayerState::IDLE);
	}
}
void Player_Zero::SitEnd()
{
	
}

void Player_Zero::SitAttackStart()
{
	// ����üũ�� �ִϸ��̼� ����
	DirCheck("Sit_Attack");
}

void Player_Zero::SitAttackUpdate(float _DeltaTime)
{
	// ���� ���� �ִϸ��̼��� ����Ϸ� �Ǿ��ٸ�
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// SIT ���·� ��ȯ
		ChangeState(PlayerState::SIT);
	}
}

void Player_Zero::SitAttackEnd()
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


