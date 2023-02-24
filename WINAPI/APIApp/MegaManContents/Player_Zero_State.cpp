#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"

void Player_Zero::ChangeState(STATEVALUE _State)
{
	m_NextState = _State;
	m_PrevState = m_StateValue;
	m_StateValue = m_NextState;

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
	case STATEVALUE::RIGHT_WALL:
		Right_Wall_Start();
		break;
	case STATEVALUE::RIGHT_WALL_JUMP:
		Right_Wall_Jump_Start();
		break;
	case STATEVALUE::LEFT_WALL:
		Left_Wall_Start();
		break;
	case STATEVALUE::LEFT_WALL_JUMP:
		Left_Wall_Jump_Start();
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
	case STATEVALUE::RIGHT_WALL:
		Right_Wall_End();
		break;
	case STATEVALUE::RIGHT_WALL_JUMP:
		Right_Wall_Jump_End();
		break;
	case STATEVALUE::LEFT_WALL:
		Left_Wall_End();
		break;
	case STATEVALUE::LEFT_WALL_JUMP:
		Left_Wall_Jump_End();
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
	case STATEVALUE::RIGHT_WALL:
		Right_Wall_Update(_DeltaTime);
		break;
	case STATEVALUE::RIGHT_WALL_JUMP:
		Right_Wall_Jump_Update(_DeltaTime);
		break;
	case STATEVALUE::LEFT_WALL:
		Left_Wall_Update(_DeltaTime);
		break;
	case STATEVALUE::LEFT_WALL_JUMP:
		Left_Wall_Jump_Update(_DeltaTime);
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
	if (true == IsFall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// ���� ���� ���� ���� �ִ� ���¶�� �÷��ش�. 
	if (true == IsHitTheGround())
	{
		// ���� �ٴڿ� �Ĺ����ִٸ� �÷��־����
		GroundCollisionCheck();
	}
	// ���� ���� �ȼ��� ������ �϶���
	if (RGB(0, 0, 0) == GetColor())
	{
		// �̵�
		if (GameEngineInput::IsPress("Left_Move") || GameEngineInput::IsPress("Right_Move"))
		{
			ChangeState(STATEVALUE::MOVE);
			return;
		}
	}

	// ���� ���� �ְ�, ����Ű�� ���ȴٸ� �������·� ��ȯ
	if (true == IsGround() && true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	// �⺻����
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
	// ���� ���� ���������� �ѹ��÷��ְ�, ���� ���� �ƴϸ� fall ���·� ����
	GroundCollisionCheck();
	if (true != IsGround())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// ���� �ƹ�Ű�� ������ ���� ���¶�� IDLE ���·� ����
	if (false == GameEngineInput::IsPress("Left_Move") &&
		false == GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// ���� ���� ���� �ְ�, ����Ű�� ���ȴٸ� �������·� ����
	if (true == IsGround() && true == GameEngineInput::IsPress("Jump"))
	{
		if (true == IsRightWall() || true == IsLeftWall())
		{
			return;
		}
		ChangeState(STATEVALUE::JUMP);
		return;
	}
	
	// ���� 
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	// �뽬Ű�� ���ȴٸ� Dash ���·� ����
	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}

	// ����Ű�� �����ִٸ� 
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		// ����Ű�� �������¿��� ����Ű�� �Է��ϸ� return
		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			return;
		}

		// ����Ű�� �������¿��� �� �������� ���� �ƴ϶�� 
		if (true != IsRightWall())
		{
			// �߷�, ���� �����ִٸ� �����ְ� 
			Gravity(_DeltaTime);
			GroundCollisionCheck();
			// �̵����� + ī�޶��̵� ���ְ� 
			SetMove(float4::Right * m_MoveSpeed * _DeltaTime);

			if (true == CameraPosCheck())
			{
				GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
			}

			AnimDirCheck("Move");
			return;
		}

	}

	// ���ʹ���
	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		// ���ʸ������� üũ���ְ�
		if (true == IsLeftOver())
		{
			return;
		}

		// ����Ű�� �������¿��� ����Ű�� ������ �ƹ����۵� ���� ����
		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			return;
		}

		// ������ ���� �ƴ� ��쿡�� �����Ѵ� 
		if (true != IsLeftWall())
		{	
			Gravity(_DeltaTime);
			GroundCollisionCheck();
			SetMove(float4::Left * m_MoveSpeed * _DeltaTime);

			if (true == CameraPosCheck())
			{
				GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
			}

			AnimDirCheck("Move");
			return;
		}
	}
}

// �ϴ� ������� �ӽ� �Ϸ� -----------------------------------------------

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
	if (true == IsTopWall())
	{
		while (false == IsTopWall())
		{
			SetMove(float4::Down * _DeltaTime);
		}

		ChangeState(STATEVALUE::FALL);
		return;
	}

	if (true == IsHitTheGround())
	{
		m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
		m_LandingSound.LoopCount(1);
		m_LandingSound.Volume(0.2f);

		GroundCollisionCheck();
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// �������¿��� ����Ű�� �Է��ϸ� ���� ���� ���·� ����
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}

	// ����Ű�� ������ �������¶�� ������ ���� �����ش�. 
	if (false == m_IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	{
		// �������¿��� Ű�� ���� ���� �ֳ�..? 
		if (true == GameEngineInput::IsDown("Jump"))
		{
			// ���? 
			m_IsJumpMax = true;
			return;
		}
		
		// Ű�� �����ִٸ� �����Ŀ��� ��� ������Ų��. 
		m_JumpPower += 80.0f;

		// ���⼭ ���� ���°� ��ÿ��� ��쿡�� �����ƽ��Ŀ��� ���� �����ϸ� �� �� ������. 
		// �����Ŀ��� ������ġ�̻� �Ѿ�ٸ�
		if (m_JumpPower >= m_JumpPowerMax)
		{
			// �����Ŀ��� ������Ű�� �ִ� ������ġ�� ����
			m_JumpPower = m_JumpPowerMax;
			m_IsJumpMax = true;
		}
	}
	m_JumpPower -= (m_GravityPower * 2.4f) * _DeltaTime;
	SetMove(float4::Up * m_JumpPower * _DeltaTime);
	
	// �� �������� ���� �ƴҶ���	
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}
	
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}
	
	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == IsLeftOver())
		{
			return;
		}

		if (true == IsLeftWall())
		{
			ChangeState(STATEVALUE::LEFT_WALL);
			return;
		}

		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}
	
	AnimDirCheck("Jump");
}

void Player_Zero::Jump_End()
{

}

void Player_Zero::Fall_Start()
{
	AnimDirCheck("Fall");
}

// ���� ������Ʈ 
// ���� �ӽÿϷ� 
void Player_Zero::Fall_Update(float _DeltaTime)
{
	// ���ϻ����� ��� �߷¿���
	Gravity(_DeltaTime);
	
	if (false == IsLeftWall() || false == IsRightWall())
	{
		GroundCollisionCheck();
	}

	// ���� ���� ���̶�� ���̵� ���·� �������ش�. 
	if (true == IsGround())
	{
		m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
		m_LandingSound.LoopCount(1);
		m_LandingSound.Volume(0.2f);

		ChangeState(STATEVALUE::IDLE);
		return;
	}
	
	if (true == GameEngineInput::IsPress("Attack"))
	{
		ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}

	if (true == IsRightWall() && true == GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::RIGHT_WALL);
		return;
	}

	if (true == IsLeftWall() && true == GameEngineInput::IsPress("Left_Move"))
	{
		ChangeState(STATEVALUE::LEFT_WALL);
		return;
	}

	
	// ������ �����̳� ��������Ű �Է½� �� �������� �������ش�. 
	if (true != IsRightWall() && true == GameEngineInput::IsPress("Right_Move"))
	{
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		AnimDirCheck("Fall_end");
		return;
	}

	if (true != IsLeftWall() && true == GameEngineInput::IsPress("Left_Move"))
	{
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}
		AnimDirCheck("Fall_end");
		return;
	}


}

void Player_Zero::Fall_End()
{

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
	// �ִϸ��̼��� ������ idle�� ����
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
		// ���� ��ø� �ϴ� ���� ���� ������ �Ǹ� 
		if (true == IsRightWall())
		{
			return;
		}

		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			return;
		}
		
		Gravity(_DeltaTime);
		SetMove(float4::Right * m_DashSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Right * m_DashSpeed * _DeltaTime);
		}
		GroundCollisionCheck();
		
		return;
	}

	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Left_Move"))
	{
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
		if (true == CameraPosCheck())
		{
		    GetLevel()->SetCameraMove(float4::Left * m_DashSpeed * _DeltaTime);	
		}
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
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	Gravity(_DeltaTime);
	GroundCollisionCheck();

	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// �� �������� ���� �ƴҶ���	
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}

		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		
		return;
	}

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == IsLeftOver())
		{
			return;
		}

		if (true == IsLeftWall())
		{
			ChangeState(STATEVALUE::LEFT_WALL);
			return;
		}

		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}
	
		return;
	}
}

void Player_Zero::Jump_Attack_End()
{
}

void Player_Zero::Right_Wall_Start()
{
	m_WallSound = GameEngineResources::GetInst().SoundPlayToControl("player_wall_effect_sound.wav");
	m_WallSound.LoopCount(1);
	m_WallSound.Volume(0.2f);
	AnimDirCheck("wall");
}

void Player_Zero::Right_Wall_Update(float _DeltaTime)
{
	// �׶��� ���°� �Ǹ� IDLE���·� ����
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}
	SetMove(float4::Down * (m_MoveSpeed* 0.5f) * _DeltaTime);

	// �Ʒ��� �������ٰ� �� �������� ���� �ƴϰ� �Ǵ� ���� ��
	if (false == IsRightWall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	if (true == IsRightWall() && true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(STATEVALUE::RIGHT_WALL_JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}

		ChangeState(STATEVALUE::FALL);
		return;
	}
}

void Player_Zero::Right_Wall_End()
{
}

void Player_Zero::Right_Wall_Jump_Start()
{
	AnimDirCheck("wall_Jump");
}

void Player_Zero::Right_Wall_Jump_Update(float _DeltaTime)
{
	// ���� �� ���� ���ε� �����Ϸ��� �Ѵٸ�
	// ���� ��ġ�� �����ش�. 
	if (true == IsTopWall())
	{
		while (false == IsTopWall())
		{
			SetMove(float4::Down * _DeltaTime);
		}

		ChangeState(STATEVALUE::FALL);
		return;
	}

	// �ִϸ��̼��� ����Ǿ��ٸ�
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// �ִϸ��̼��� ����Ƚ����� ���������� ���̶�� RIHGTWALL 
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}

		// ���� ���ϻ��¶�� FALL
		if (true == IsFall())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}
	}

	SetMove(float4::Up * m_WallJumpPower * _DeltaTime);
}

void Player_Zero::Right_Wall_Jump_End()
{
}

void Player_Zero::Left_Wall_Start()
{
	m_WallSound = GameEngineResources::GetInst().SoundPlayToControl("player_wall_effect_sound.wav");
	m_WallSound.LoopCount(1);
	m_WallSound.Volume(0.2f);
	AnimDirCheck("wall");
}

void Player_Zero::Left_Wall_Update(float _DeltaTime)
{
	// �׶��� ���°� �Ǹ� IDLE���·� ����
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	SetMove(float4::Down * (m_MoveSpeed * 0.5f) * _DeltaTime);

	// �Ʒ��� �������ٰ� �� ������ ���� �ƴϰ� �Ǵ� ���� ��
	if (false == IsLeftWall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	if (true == IsLeftWall() && true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(STATEVALUE::LEFT_WALL_JUMP);
		return;
	}

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		if(true == CameraPosCheck())
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		
		ChangeState(STATEVALUE::FALL);
		return;
	}
}

void Player_Zero::Left_Wall_End()
{
}

void Player_Zero::Left_Wall_Jump_Start()
{
	AnimDirCheck("wall_Jump");
}

void Player_Zero::Left_Wall_Jump_Update(float _DeltaTime)
{
	if (true == IsTopWall())
	{
		while (false == IsTopWall())
		{
			SetMove(float4::Down * _DeltaTime);
		}

		ChangeState(STATEVALUE::FALL);
		return;
	}

	if (true == m_AnimationRender->IsAnimationEnd())
	{
		if (true == IsLeftWall())
		{
			ChangeState(STATEVALUE::LEFT_WALL);
			return;
		}

		if (true == IsFall())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}
	}

	SetMove(float4::Up * m_WallJumpPower * _DeltaTime);
}

void Player_Zero::Left_Wall_Jump_End()
{
}
