#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	case PlayerState::RIDEUP:
		RideUpStart();
		break;
	case PlayerState::RIDEUP_ATTACK:
		RideUpAttackStart();
		break;
	case PlayerState::JUMP_ATTACK:
		JumpAttackStart();
		break;
	case PlayerState::WALL:
		WallStart();
		break;
	case PlayerState::WALL_ATTACK:
		WallAttackStart();
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
	case PlayerState::ATTACK_FIRST:
		Attack_First_Start();
		break;
	case PlayerState::ATTACK_SECOND:
		Attack_Second_Start();
		break;
	case PlayerState::ATTACK_THIRD:
		Attack_Third_Start();
		break;
	case PlayerState::DOUBLEJUMP:
		DoubleJumpStart();
		break;
	case PlayerState::HIT:
		HitStart();
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
	case PlayerState::RIDEUP:
		RideUpEnd();
		break;
	case PlayerState::RIDEUP_ATTACK:
		RideUpAttackEnd();
		break;
	case PlayerState::JUMP_ATTACK:
		JumpAttackEnd();
		break;
	case PlayerState::WALL:
		WallEnd();
		break;
	case PlayerState::WALL_ATTACK:
		WallAttackEnd();
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
	case PlayerState::ATTACK_FIRST:
		Attack_First_End();
		break;
	case PlayerState::ATTACK_SECOND:
		Attack_Second_End();
		break;
	case PlayerState::ATTACK_THIRD:
		Attack_Third_End();
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
	case PlayerState::RIDEUP:
		RideUpUpdate(_DeltaTime);
		break;
	case PlayerState::RIDEUP_ATTACK:
		RideUpUpdate(_DeltaTime);
		break;
	case PlayerState::JUMP_ATTACK:
		JumpAttackUpdate(_DeltaTime);
		break;
	case PlayerState::WALL:
		WallUpdate(_DeltaTime);
		break;
	case PlayerState::WALL_ATTACK:
		WallAttackUpdate(_DeltaTime);
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
	case PlayerState::ATTACK_FIRST:
		Attack_First_Update(_DeltaTime);
		break;
	case PlayerState::ATTACK_SECOND:
		Attack_Second_Update(_DeltaTime);
		break;
	case PlayerState::ATTACK_THIRD:
		Attack_Third_Update(_DeltaTime);
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
	m_Ground = true;
}

void Player_Zero::IdleStart()
{
	m_Ground = true;
	DirCheck("idle");
}

void Player_Zero::IdleUpdate(float _DeltaTime)
{
	// Idle ������ ��� ����, ������ Ű�� ���ȴٸ� Move ���·� �����Ѵ�.  
	if (true == m_Ground)
	{
		if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
		{
			ChangeState(PlayerState::MOVE);
			return;
		}

		if (GameEngineInput::IsPress("Attack"))
		{
			ChangeState(PlayerState::ATTACK_FIRST);
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
	// ���� �浹üũ 
	/*if (true == m_Collision->Collision({ .TargetGroup = static_cast<int>(COLORDER::MONSTER) }))
	{
		ChangeState(PlayerState::HIT);
		return;
	}*/


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
		ChangeState(PlayerState::ATTACK_FIRST);
		return;
	}

	if (GameEngineInput::IsPress("Jump"))
	{
		ChangeState(PlayerState::JUMP);
		return;
	}
	if (GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::DASH);
		return;
	}

	/*if (GameEngineInput::IsDown("Sit"))
	{
		ChangeState(PlayerState::SIT);
		return;
	}*/

	DirCheck("Move");
}



void Player_Zero::MoveEnd()
{
}

// �Ϲݰ��� 
void Player_Zero::Attack_First_Start()
{
	DirCheck("normal_attack_first");
}

void Player_Zero::Attack_First_Update(float _Time)
{
	// ������ ������ �����ӿ� �����ϸ� Idle ���·� �������ش�. 
	// �ϴ� �ӽ÷� �����صΰ�, ���߿� ���鶧 �븻���� 1Ÿ, 23Ÿ ���·� �����ؼ� �����Ѵ�. 
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	// 1Ÿ ����� ������ ���� ���¿��� X Ű�� �ѹ� �� ������ 2Ÿ����
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATTACK_SECOND);
		return;
	}

}

void Player_Zero::Attack_First_End()
{
}

void Player_Zero::Attack_Second_Start()
{
	DirCheck("normal_attack_second");
}

void Player_Zero::Attack_Second_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::ATTACK_THIRD);
		return;
	}
}

void Player_Zero::Attack_Second_End()
{
}

void Player_Zero::Attack_Third_Start()
{
	DirCheck("normal_attack_third");
}

void Player_Zero::Attack_Third_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
}

void Player_Zero::Attack_Third_End()
{
}


// �׳� ���� Ŭ���� ���� ����� �ٷ� �ذ��ϰ� ������
// Ŭ���� �����, �뽬��ŸƮ�ϸ� ����, Ŭ���� ��ü ������Ʈ������ �ð������� ����
// ����ó���ѰŴ� ���� ������� ��������ϱ� 
void Player_Zero::DashStart()
{
	// ��� ��ŸƮ������ ����Ʈ�������� ������Ʈ���¸� on���� ����
	DirCheck("Dash");
	/*if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_EffectRender->SetPosition(float4{ -250 , 0 });
		m_EffectRender->ChangeAnimation(m_DirString + "dash_effect");
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_EffectRender->SetPosition(float4{ 250 , 0 });
		m_EffectRender->ChangeAnimation(m_DirString + "dash_effect");
	}*/
}

void Player_Zero::DashUpdate(float _Time)
{
	// �뽬������Ʈ������ ���߻��¿��� �뽬 ����� ����Ǹ� 
	// ���ϸ������ �ٲ�����. �ᱹ �׳� ���ϸ���� ���� �ؾߵǳ� 
	if (true == m_AnimationRender->IsAnimationEnd())
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
	m_Jump = true;
	m_MoveDir += float4::Up * 400.0f;
	DirCheck("Jump");
}

void Player_Zero::JumpUpdate(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		if (true == m_Ground)
		{
			ChangeState(PlayerState::IDLE);
			return;
		}
		
		else if (false == m_Ground)
		{
			m_AnimationRender->SetFrame(31);
		}
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::JUMP_ATTACK);
		return;
	}

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(PlayerState::DASH);
		return;
	}
	// ����Ű �߿� �ݴ����Ű�� ������ �������� �ִϸ��̼��� �ٲ�����. 
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		return;
	}

	if (true == GameEngineInput::IsPress("RightMove"))
	{
		return;
	}
}

void Player_Zero::JumpEnd()
{
	m_Jump = false;
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
		if (true == m_Ground)
		{
			ChangeState(PlayerState::IDLE);
		}
	
		return;
	}
}

void Player_Zero::JumpAttackEnd()
{
}

void Player_Zero::RideUpStart()
{
	DirCheck("rideup");
}

void Player_Zero::RideUpUpdate(float _DeltaTime)
{
	// ��� �Ŵ޷� �ִ� ���¶�� ���� �������� ����
	// ������ �ִ� ���¶�� �ִϸ��̼� ����. ��. 
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::RIDEUP_ATTACK);
		return;
	}
}

void Player_Zero::RideUpEnd()
{
}

void Player_Zero::RideUpAttackStart()
{
	DirCheck("Rideup_attack");
}

void Player_Zero::RideUpAttackUpdate(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// �ִϸ��̼� ������ �ٽ� ��ٸ� ź �������.  ��. 
		return;
	}
}

void Player_Zero::RideUpAttackEnd()
{
}

void Player_Zero::WallStart()
{
	DirCheck("wall");
}

void Player_Zero::WallUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(PlayerState::WALL_ATTACK);
		return;
	}
}

void Player_Zero::WallEnd()
{
}

void Player_Zero::WallAttackStart()
{
	DirCheck("wall_attack");
}

void Player_Zero::WallAttackUpdate(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::WALL);
		return;
	}
}

void Player_Zero::WallAttackEnd()
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


