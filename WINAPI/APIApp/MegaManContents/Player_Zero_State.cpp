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
	case STATEVALUE::WALL:
		Wall_Start();
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
	case STATEVALUE::WALL:
		Wall_End();
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
	case STATEVALUE::WALL:
		Wall_Update(_DeltaTime);
		break;
	}
}

// -----------------���� �Ϸ�---------------------
void Player_Zero::Recall_Start()
{
	m_RecallSound = GameEngineResources::GetInst().SoundPlayToControl("player_recall_sound.wav");
	m_RecallSound.LoopCount(1);
	m_RecallSound.Volume(0.2f);
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
	// ���� �� ���������� ���̵�� �ٲ��, ���̵�� �ٲ�¼��� ���긦 ������ �̵��� �Ǳ� ������ �ڲ� 
	// �Ͼ������ �İ���� ���� �ö���°� ������

	// �̵�
	if (GameEngineInput::IsPress("Left_Move") || GameEngineInput::IsPress("Right_Move"))
	{

		ChangeState(STATEVALUE::MOVE);
		return;
	}

	// ���� ���� ���� �Ĺ��� �ִٸ� �÷��ش�. 
	if (true == IsHitTheGround())
	{
		// ���� �ٴڿ� �Ĺ����ִٸ� �÷��־����
		GroundCollisionCheck();
		return;
	}

	// ���� 
	if (true == IsGround() && true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	// �뽬
	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}
}

void Player_Zero::Idle_End()
{
}

// �̵����۽� ����+�ִϸ��̼�üũ
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

	// ������ ����
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			return;
		}

		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			return;
		}

		// �߷��ְ� 
		Gravity(_DeltaTime);
		GroundCollisionCheck();
		if (false == IsGround())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}
		
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		
		AnimDirCheck("Move");
		return;
	}

	// ���ʹ���
	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		// ���ʸ������� üũ
		if (true == IsLeftWall() || true == IsLeftOver())
		{
			return;
		}

		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			return;
		}

		Gravity(_DeltaTime);
		GroundCollisionCheck();
		if (false == IsGround())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}

		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		AnimDirCheck("Move");
		return;
	}

}

void Player_Zero::Move_End()
{

}

// ���ڵ� ������ŸƮ
//m_Jump = true;
//IsJumpMax = false;
//
//m_JumpPower = 50.0f;
//m_GravityPower = 800.0f;


// ���ڵ� ����������Ʈ
	//if (false == IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	//{
	//	// Ű�� �����ִٸ� �����Ŀ��� ��� ������Ų��. 
	//	m_JumpPower += 500.0f * _DeltaTime;

	//	// �����Ŀ��� ������ġ�̻� �Ѿ�ٸ�
	//	if (m_JumpPower >= 100.0f)
	//	{
	//		// �����Ŀ��� ?
	//		m_JumpPower = 100.0f;
	//		IsJumpMax = true;
	//	}
	// 
	//m_MoveDir += float4::Up * m_JumpPower;
	//m_JumpPower -= m_GravityPower * _DeltaTime;


void Player_Zero::Jump_Start()
{
	// �������
	m_JumpSound = GameEngineResources::GetInst().SoundPlayToControl("player_jump_sound.wav");
	m_JumpSound.LoopCount(1);
	m_JumpSound.Volume(0.2f);

	m_IsJumpMax = false;
	m_JumpPower = 50.0f;

	AnimDirCheck("Jump");
}

void Player_Zero::Jump_Update(float _DeltaTime)
{
	if (true == IsHitTheGround())
	{
		GroundCollisionCheck();
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// ����Ű�� ������ �������¶�� ������ ���� �����ش�. 
	if (false == m_IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	{
		// �� ���⼭ ������ �ѹ� �������� �׳� ������ ������ѹ��� 
		if (true == GameEngineInput::IsDown("Jump"))
		{
			// ���? 
			m_IsJumpMax = true;
			return;
		}
		
		// Ű�� �����ִٸ� �����Ŀ��� ��� ������Ų��. 
		m_JumpPower += 60.0f;

		// �����Ŀ��� ������ġ�̻� �Ѿ�ٸ�
		if (m_JumpPower >= m_JumpPowerMax)
		{
			// �����Ŀ��� ������Ű�� �ִ� ������ġ�� ����
			m_JumpPower = m_JumpPowerMax;
			m_IsJumpMax = true;
		}
	}

	m_JumpPower -= (m_GravityPower * 2.1f) * _DeltaTime;
	SetMove(float4::Up * m_JumpPower * _DeltaTime);

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (false == IsRightWall())
		{
			SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}

		/*else if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::WALL);
			return;
		}*/

		return;
	}

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == IsLeftOver())
		{
			return;
		}

		if (false == IsLeftWall())
		{
			SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}
		return;
	}
	AnimDirCheck("Jump");
}

void Player_Zero::Jump_End()
{
	m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
	m_LandingSound.LoopCount(1);
	m_LandingSound.Volume(0.2f);
}

void Player_Zero::Fall_Start()
{
	AnimDirCheck("Fall");
}

// ���� ������Ʈ���� üũ�ؾ��� ��
void Player_Zero::Fall_Update(float _DeltaTime)
{
	Gravity(_DeltaTime);
	if (true == IsHitTheGround())
	{
		GroundCollisionCheck();
	}

	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// ����Ű �Է½� ��������
	if (true == GameEngineInput::IsDown("Attack"))
	{
		//ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		AnimDirCheck("Fall_end");
		return;
	}

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		AnimDirCheck("Fall_end");
		return;
	}
}

void Player_Zero::Fall_End()
{
	m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
	m_LandingSound.LoopCount(1);
	m_LandingSound.Volume(0.2f);
}

void Player_Zero::Attack_First_Start()
{
	m_AttackSound = GameEngineResources::GetInst().SoundPlayToControl("player_attack_first.wav");
	m_AttackSound.LoopCount(1);
	m_AttackSound.Volume(0.2f);

	m_SaberSound = GameEngineResources::GetInst().SoundPlayToControl("player_saber_sound.wav");
	m_SaberSound.LoopCount(1);
	m_SaberSound.Volume(0.2f);
	
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

	if (true == GameEngineInput::IsDown("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}

}

void Player_Zero::Attack_First_End()
{
}

void Player_Zero::Attack_Second_Start()
{
	m_AttackSound = GameEngineResources::GetInst().SoundPlayToControl("player_attack_second.wav");
	m_AttackSound.LoopCount(1);
	m_AttackSound.Volume(0.2f);

	m_SaberSound = GameEngineResources::GetInst().SoundPlayToControl("player_saber_sound.wav");
	m_SaberSound.LoopCount(1);
	m_SaberSound.Volume(0.2f);

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
	m_AttackSound = GameEngineResources::GetInst().SoundPlayToControl("player_attack_third.wav");
	m_AttackSound.LoopCount(1);
	m_AttackSound.Volume(0.2f);

	m_SaberSound = GameEngineResources::GetInst().SoundPlayToControl("player_saber_sound.wav");
	m_SaberSound.LoopCount(1);
	m_SaberSound.Volume(0.2f);

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
	m_DashSound = GameEngineResources::GetInst().SoundPlayToControl("player_dash_sound.wav");
	m_DashSound.LoopCount(1);
	m_DashSound.Volume(0.2f);
	AnimDirCheck("Dash");
}

void Player_Zero::Dash_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	if (false == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	if (true == GameEngineInput::IsPress("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	// �̵������ۼ�
	// �׳��̵��̶� �Ȱ����ϰ� ���꽺�ǵ带 �뽬���ǵ�� �ٲٸ� �� �� ����.  
	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			SetMove(float4::Zero);
			return;
		}

		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			return;
		}
		
		Gravity(_DeltaTime);
		SetMove(float4::Right * m_DashSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_DashSpeed * _DeltaTime);
		GroundCollisionCheck();
		
		return;
	}

	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == IsRightWall())
		{
			SetMove(float4::Zero);
			return;
		}

		if (true == IsLeftOver())
		{
			return;
		}

		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			return;
		}

		Gravity(_DeltaTime);
		SetMove(float4::Left * m_DashSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Left * m_DashSpeed * _DeltaTime);
		GroundCollisionCheck();	
		return;
	}

	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}
	
}

void Player_Zero::Dash_End()
{
	m_DashSound.Stop();
}

void Player_Zero::Jump_Attack_Start()
{
	m_SaberSound = GameEngineResources::GetInst().SoundPlayToControl("player_saber_sound.wav");
	m_SaberSound.LoopCount(1);
	m_SaberSound.Volume(0.2f);

	AnimDirCheck("Jump_Attack");
}

void Player_Zero::Jump_Attack_Update(float _DeltaTime)
{
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}
}

void Player_Zero::Jump_Attack_End()
{
}

void Player_Zero::Wall_Start()
{
	AnimDirCheck("wall");
}

void Player_Zero::Wall_Update(float _DeltaTime)
{
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	SetMove(float4::Down * (m_MoveSpeed* 0.7f) * _DeltaTime);
	GroundCollisionCheck();

	// �ӽ÷� ���� �ѹ� �־
	// ��Ÿ�������� ������ �ƴϰ� Down ���� �ѹ���, ������ ������ �ణ �����ϵ��� ��������. 
	if (true == GameEngineInput::IsPress("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}
}

void Player_Zero::Wall_End()
{
}
