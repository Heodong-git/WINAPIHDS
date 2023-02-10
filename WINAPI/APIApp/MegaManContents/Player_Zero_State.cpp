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
void Player_Zero::ChangeState(STATEVALUE _State)
{
	// �÷��̾��� ���� ���¸� �޾ƿ´�. 
	m_NextState = _State;
	// �÷��̾��� ���� ���´� ���� ���°� �ȴ�. 
	m_PrevState = m_StateValue;
	// ���� ���¸� ����� ���·� �����Ѵ�. 
	m_StateValue = m_NextState;

	// ���� ���°��� �����̳Ŀ� ���� Start �Լ� ȣ��
	switch (m_NextState)
	{
	case STATEVALUE::RECALL:
		Recall_Start();
		break;
	case STATEVALUE::IDLE:
		Idle_Start();
		break;
	case STATEVALUE::MOVE:
		Move_Start();
		break;
	case STATEVALUE::JUMP:
		Jump_Start();
		break;
	case STATEVALUE::FALL:
		Fall_Start();
		break;
	case STATEVALUE::FALL_END:
		Fall_End_Start();
		break;
	case STATEVALUE::ATTACK_FIRST:
		Attack_First_Start();
		break;
	case STATEVALUE::ATTACK_SECOND:
		Attack_Second_Start();
		break;
	case STATEVALUE::ATTACK_THIRD:
		Attack_Third_Start();
		break;
	case STATEVALUE::DASH:
		Dash_Start();
		break;
	case STATEVALUE::JUMP_ATTACK:
		Jump_Attack_Start();
		break;
	}

	// ���� ������ Start �Լ��� ȣ�� �� ���Ŀ� 
	// ���� ������ End �Լ��� ȣ���Ͽ� ������ �۾��� �����Ѵ�. 
	switch (m_PrevState)
	{
	case STATEVALUE::RECALL:
		Recall_End();
		break;
	case STATEVALUE::IDLE:
		Idle_End();
		break;
	case STATEVALUE::MOVE:
		Move_End();
		break;
	case STATEVALUE::JUMP:
		Jump_End();
		break;
	case STATEVALUE::FALL:
		Fall_End();
		break;
	case STATEVALUE::FALL_END:
		Fall_End_End();
		break;
	case STATEVALUE::ATTACK_FIRST:
		Attack_First_End();
		break;
	case STATEVALUE::ATTACK_SECOND:
		Attack_Second_End();
		break;
	case STATEVALUE::ATTACK_THIRD:
		Attack_Third_End();
		break;
	case STATEVALUE::DASH:
		Dash_End();
		break;
	case STATEVALUE::JUMP_ATTACK:
		Jump_Attack_End();
		break;
	}
}

void Player_Zero::UpdateState(float _DeltaTime)
{
	// ���� ���°��� ���� �б�ó��
	switch (m_StateValue)
	{
	case STATEVALUE::RECALL:
		Recall_Update(_DeltaTime);
		break;
	case STATEVALUE::IDLE:
		Idle_Update(_DeltaTime);
		break;
	case STATEVALUE::MOVE:
		Move_Update(_DeltaTime);
		break;
	case STATEVALUE::JUMP:
		Jump_Update(_DeltaTime);
		break;
	case STATEVALUE::FALL:
		Fall_Update(_DeltaTime);
		break;
	case STATEVALUE::FALL_END:
		Fall_End_Update(_DeltaTime);
		break;
	case STATEVALUE::ATTACK_FIRST:
		Attack_First_Update(_DeltaTime);
		break;
	case STATEVALUE::ATTACK_SECOND:
		Attack_Second_Update(_DeltaTime);
		break;
	case STATEVALUE::ATTACK_THIRD:
		Attack_Third_Update(_DeltaTime);
		break;
	case STATEVALUE::DASH:
		Dash_Update(_DeltaTime);
		break;
	case STATEVALUE::JUMP_ATTACK:
		Jump_Attack_Update(_DeltaTime);
		break;
	}
}

void Player_Zero::Recall_Start()
{
	// �÷��̾� ����üũ + �ִϸ��̼� ���
	AnimDirCheck("recall");
}

void Player_Zero::Recall_Update(float _DeltaTime)
{
	// �ִϸ��̼��� ���� �Ǿ��ٸ� ���̵�� ��ȯ
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return; 
	}

	//// �ִϸ��̼� �����߿� ����, ������Ű�� ������ �ƹ��͵� �������� �ʵ��� ����ó��
	//if (true == GameEngineInput::IsPress("Left_Move") || 
	//	true == GameEngineInput::IsPress("Right_Move"))
	//{
	//	return;
	//}
}

void Player_Zero::Recall_End()
{
}

void Player_Zero::Idle_Start()
{
	// ����üũ �� �ִϸ��̼� ���
	AnimDirCheck("Idle");
}

void Player_Zero::Idle_Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("Left_Move") || GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::MOVE);
		return;
	}

	// ������ üũ�ؾ� ����̾�? ���̾�?

	//if (false == IsGround())
	//{
	//	ChangeState(STATEVALUE::FALL);
	//	return;
	//}

	if (true == IsGround())
	{
		GroundCollisionCheck();
		// �÷������.
		// ChangeState(STATEVALUE::FALL);
		return;
	}


	// ���̵� ���¿��� ���� ��ư �ѹ� ���ȴٸ� ���� ���·� ��ȯ�Ѵ�. 
	if (true == GameEngineInput::IsPress("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}
}

void Player_Zero::Idle_End()
{
}

void Player_Zero::Move_Start()
{
	AnimDirCheck("Move");
}

void Player_Zero::Move_Update(float _DeltaTime)
{
	// �¿�Ű�� ���� ���°� �ƴ϶�� ���̵�� ��ȯ
	if (false == GameEngineInput::IsPress("Left_Move") &&
		false == GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	if (true == GameEngineInput::IsPress("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		m_MoveDir += float4::Left * m_MoveSpeed;
		AnimDirCheck("Move");
		return;
	}

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		m_MoveDir += float4::Right * m_MoveSpeed;
		AnimDirCheck("Move");
		return;
	}
}

void Player_Zero::Move_End()
{

}

void Player_Zero::Jump_Start()
{
	// �رٻ� 
	// �������¸� true 
	m_Jump = true;
	IsJumpMax = false;

	// ������ ���۵Ǹ� �⺻ �����Ŀ��� 30����.
	m_JumpPower = 50.0f;
	m_GravityPower = 800.0f;

	AnimDirCheck("Jump");
}

void Player_Zero::Jump_Update(float _DeltaTime)
{
	// ���� ������ �ִ���̰� �ƴϰ�, ����Ű�� �����ִٸ� ����
	if (false == IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	{
		// Ű�� �����ִٸ� �����Ŀ��� ��� ������Ų��. 
		m_JumpPower += 500.0f * _DeltaTime;

		// �����Ŀ��� ������ġ�̻� �Ѿ�ٸ�
		if (m_JumpPower >= 100.0f)
		{
			// �����Ŀ��� ?
			m_JumpPower = 100.0f;
			IsJumpMax = true;
		}
	}

	m_MoveDir += float4::Up * m_JumpPower;
	m_JumpPower -= m_GravityPower * _DeltaTime;

	/*if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}*/
}

void Player_Zero::Jump_End()
{
	m_Jump = false;
	ChangeState(STATEVALUE::IDLE);
}

void Player_Zero::Fall_Start()
{
	/*m_Falling = true;
	if (m_PrevState == STATEVALUE::JUMP_ATTACK)
	{
		AnimDirCheck("Fall_end");
		return;
	}
	AnimDirCheck("Fall");*/
}

void Player_Zero::Fall_Update(float _DeltaTime)
{
	//if (true == m_AnimationRender->IsAnimationEnd() && false == m_Falling)
	//{
	//	ChangeState(STATEVALUE::IDLE);
	//	return;
	//}

	//if (true == GameEngineInput::IsDown("Attack"))
	//{
	//	ChangeState(STATEVALUE::JUMP_ATTACK);
	//	return;
	//}
	//
	//// �浹üũ�� �ؼ� �ȼ��� ���� 255 0 255 ��� Ground = true; 

	//GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColMap_Spaceport.BMP");
	//if (nullptr == ColImage)
	//{
	//	MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	//}

	//float4 NextPos = GetPos() + m_MoveDir * _DeltaTime; 
	//if (RGB(57, 255, 20) == ColImage->GetPixelColor(NextPos, RGB(57, 255, 20)))
	//{
	//	m_Falling = false;
	//}
}

void Player_Zero::Fall_End()
{
}

void Player_Zero::Fall_End_Start()
{
	AnimDirCheck("Fall_End");
}

void Player_Zero::Fall_End_Update(float _DeltaTime)
{
}

void Player_Zero::Fall_End_End()
{
}

void Player_Zero::Attack_First_Start()
{
	AnimDirCheck("normal_attack_first");
}

void Player_Zero::Attack_First_Update(float _Time)
{
	// ������ ������ �����ӿ� �����ϸ� Idle ���·� �������ش�. 
	// �ϴ� �ӽ÷� �����صΰ�, ���߿� ���鶧 �븻���� 1Ÿ, 23Ÿ ���·� �����ؼ� �����Ѵ�. 
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// 1Ÿ ����� ������ ���� ���¿��� X Ű�� �ѹ� �� ������ 2Ÿ����
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_SECOND);
		return;
	}

}

void Player_Zero::Attack_First_End()
{
}

void Player_Zero::Attack_Second_Start()
{
	AnimDirCheck("normal_attack_second");
}

void Player_Zero::Attack_Second_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_THIRD);
		return;
	}
}

void Player_Zero::Attack_Second_End()
{
}

void Player_Zero::Attack_Third_Start()
{
	AnimDirCheck("normal_attack_third");
}

void Player_Zero::Attack_Third_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}
}

void Player_Zero::Attack_Third_End()
{
}

void Player_Zero::Dash_Start()
{
	AnimDirCheck("Dash");
}

void Player_Zero::Dash_Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// �̵������ۼ�
	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Right_Move"))
	{
		return;
	}

	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Left_Move"))
	{
		return;
	}

	//
	
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}
	
}

void Player_Zero::Dash_End()
{
}

void Player_Zero::Jump_Attack_Start()
{
	AnimDirCheck("Jump_Attack");
}

void Player_Zero::Jump_Attack_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		AnimDirCheck("Fall_end");
		ChangeState(STATEVALUE::FALL);
		return;
	}
}

void Player_Zero::Jump_Attack_End()
{
}
