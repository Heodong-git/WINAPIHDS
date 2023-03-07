#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Ladder.h"
#include "Effect_Dash.h"
#include "SpacePortLevel.h"
#include "Object_Door.h"

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
	case STATEVALUE::RIDE_UP:
		RideUp_Start();
		break;
	case STATEVALUE::DOOR_CONTACT:
		Door_Contact_Start();
		break;
	case STATEVALUE::HIT:
		Hit_Start();
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
	case STATEVALUE::RIDE_UP:
		RideUp_End();
		break;
	case STATEVALUE::DOOR_CONTACT:
		Door_Contact_End();
		break;
	case STATEVALUE::HIT:
		Hit_End();
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
	case STATEVALUE::RIDE_UP:
		RideUp_Update(_DeltaTime);
		break;
	case STATEVALUE::DOOR_CONTACT:
		Door_Contact_Update(_DeltaTime);
		break;
	case STATEVALUE::HIT:
		Hit_Update(_DeltaTime);
		break;
	}
}

// -----------------���� �Ϸ�---------------------
void Player_Zero::Recall_Start()
{
	m_SpLevel = dynamic_cast<SpacePortLevel*>(GetLevel());
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

	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_BULLET), .TargetColType = CT_CirCle, .ThisColType = CT_CirCle }))
	{
		ChangeState(STATEVALUE::HIT);
		return;
	}

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
		// �������� �������̰�, ���� �̵� ��ġ�� ���� X���� ������ �Ѿ�ٸ� �̵����� �ʰ� return 
		if (true == m_IsBossFight && true == IsBossRoomRightOver())
		{
			return;
		}

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

			// ī�޶���ġ��갪�� true, ���� �ö󰡴� ������ �ƴ� ��쿡�� �̷��� ó��.
			if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
			{
				GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
			}

			else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
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
		if (true == m_IsBossFight && true == IsBossRoomLeftOver())
		{
			return;
		}
		// ���ʸ������� üũ���ְ�
		if (true == IsLeftOver())
		{
			return;
		}

		// ���⼭ ���� �������� ����� ������ ���ؼ� ����ٸ� retrun ���� 

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

			if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
			{
				GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
			}

			else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
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
	if (true == GameEngineInput::IsPress("Up_Move"))
	{
		// �������¿��� ������ Ű�� ������ �ִ� ���¿��� 
		// ���� ���� ��ٸ��� �浹ü�� �浹�ߴٸ� climb ���·� ����
		// ���⼭ if �����
		// ���� �浹üũ , �׸��� �浹�� �༮�� �����ͼ� �׳༮�� x ��� �����ϰ� �÷��̾��� x�� ��ǥ�� �����Ѵ�
		std::vector<GameEngineCollision*> vecCollision;
		if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_LADDER), .TargetColType = CT_Rect, .ThisColType = CT_Rect} , vecCollision))
		{
			// ���⼭ x�� ��ǥ�� �浹�� ��ٸ��༮�� �����ϰ� �����ؾ���. �ϴ� �̰ź���
			// ���⼭ �浹ü�� ���ʰ� ��ٸ�������Ʈ��� x���� ��ġ�� �����ϰ� �������ش�. 
			for (size_t i = 0; i < vecCollision.size(); ++i)
			{
				Ladder* ColLadder = vecCollision[i]->GetOwner<Ladder>();
				if (nullptr != ColLadder)
				{
					float4 LadderPos = ColLadder->GetPos();
					float LadderPosX = LadderPos.x;
					float MovePosX = LadderPos.x - GetPos().x;
					SetMove(float4{ MovePosX , 0 });
				}
			}
			ChangeState(STATEVALUE::RIDE_UP);
			return;
		}
	}

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
	m_JumpPower -= (m_GravityPower * m_GravityMgf) * _DeltaTime;
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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
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
	if (true == GameEngineInput::IsPress("Up_Move"))

	{
		// �������¿��� ������ Ű�� ������ �ִ� ���¿��� 
		// ���� ���� ��ٸ��� �浹ü�� �浹�ߴٸ� climb ���·� ����
		// ���⼭ if �����
		// ���� �浹üũ , �׸��� �浹�� �༮�� �����ͼ� �׳༮�� x ��� �����ϰ� �÷��̾��� x�� ��ǥ�� �����Ѵ�
		std::vector<GameEngineCollision*> vecCollision;
		if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_LADDER), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, vecCollision))
		{
			// ���⼭ x�� ��ǥ�� �浹�� ��ٸ��༮�� �����ϰ� �����ؾ���. �ϴ� �̰ź���
			// ���⼭ �浹ü�� ���ʰ� ��ٸ�������Ʈ��� x���� ��ġ�� �����ϰ� �������ش�. 
			for (size_t i = 0; i < vecCollision.size(); ++i)
			{
				Ladder* ColLadder = vecCollision[i]->GetOwner<Ladder>();
				if (nullptr != ColLadder)
				{
					float4 LadderPos = ColLadder->GetPos();
					float LadderPosX = LadderPos.x;
					float MovePosX = LadderPos.x - GetPos().x;
					SetMove(float4{ MovePosX , 0 });
				}
			}
			ChangeState(STATEVALUE::RIDE_UP);
			return;
		}
	}

	// ���ϻ����� ��� �߷¿���
	Gravity(_DeltaTime);
	
	if (false == IsLeftWall() || false == IsRightWall())
	{
		GroundCollisionCheck();
	}

	// ���� ���� ���̶�� ���̵� ���·� �������ش�. 
	if (true == IsGround())
	{
		if (m_PrevState != STATEVALUE::RIDE_UP)
		{
			m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
			m_LandingSound.LoopCount(1);
			m_LandingSound.Volume(0.2f);
		}

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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}

		AnimDirCheck("Fall_end");
		return;
	}

	if (true != IsLeftWall() && true == GameEngineInput::IsPress("Left_Move"))
	{
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
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
	
	// ���⼭ �ִϸ��̼��� ���
	AnimDirCheck("normal_attack_first");
}

void Player_Zero::Attack_First_Update(float _Time)
{
	const char* Dir = GetDirString().c_str();
	// ���⼭ ���� ������ �޾ƿ���, �� ������ ���Ŀ� ���� �տ��ٰ� �浹ü ����
	if (0 == strcmp(Dir, "Right_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_RightNormalAttackPos);
	}
	
	else if (0 == strcmp(Dir, "Left_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_LeftNormalAttackPos);
	}

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
	m_SaberCollider->Off();
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
	// ���⼭ ���� ������ �޾ƿ���, �� ������ ���Ŀ� ���� �տ��ٰ� �浹ü ����
	const char* Dir = GetDirString().c_str();
	if (0 == strcmp(Dir, "Right_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_RightNormalAttackPos);
	}

	else if (0 == strcmp(Dir, "Left_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_LeftNormalAttackPos);
	}

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
	m_SaberCollider->Off();
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
	// ���⼭ ���� ������ �޾ƿ���, �� ������ ���Ŀ� ���� �տ��ٰ� �浹ü ����
	const char* Dir = GetDirString().c_str();
	if (0 == strcmp(Dir, "Right_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->SetScale(float4{ 300, 300 });
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_RightNormalAttackPos);
	}

	else if (0 == strcmp(Dir, "Left_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->SetScale(float4{ 300, 300 });
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_LeftNormalAttackPos);
	}

	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}
}

void Player_Zero::Attack_Third_End()
{
	m_SaberCollider->Off();
	m_SaberCollider->SetScale(m_SaberColliderScale);
}

void Player_Zero::Dash_Start()
{
	m_DashSound = GameEngineResources::GetInst().SoundPlayToControl("player_dash_sound.wav");
	m_DashSound.LoopCount(1);
	m_DashSound.Volume(0.2f);

	const char* Dir = GetDirString().c_str();
	Effect_Dash* Dash = GetLevel()->CreateActor<Effect_Dash>(ZORDER::PLAYER_EFFECT);
	if (0 == strcmp(Dir, "Right_"))
	{
		Dash->SetPos(GetPos() - m_DashDistance);
		Dash->m_AnimationRender->ChangeAnimation("right_dash_effect");
	}

	else if (0 == strcmp(Dir, "Left_"))
	{
		Dash->SetPos(GetPos() + m_DashDistance);
		Dash->m_AnimationRender->ChangeAnimation("left_dash_effect");
	}
	// ����ٰ� 
	AnimDirCheck("Dash");
}

void Player_Zero::Dash_Update(float _DeltaTime)
{
	std::vector<GameEngineCollision*> vecCollision;
	if (true == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_DOOR), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, vecCollision))
	{
		// ���⼭ x�� ��ǥ�� �浹�� ��ٸ��༮�� �����ϰ� �����ؾ���. �ϴ� �̰ź���
		// ���⼭ �浹ü�� ���ʰ� ��ٸ�������Ʈ��� x���� ��ġ�� �����ϰ� �������ش�. 
		for (size_t i = 0; i < vecCollision.size(); ++i)
		{
			Object_Door* ColDoor = vecCollision[i]->GetOwner<Object_Door>();
			if (nullptr != ColDoor)
			{
				int a = 0;
			}
		}
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
		if (true == m_IsBossFight && true == IsBossRoomRightOver())
		{
			return;
		}

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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_DashSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}
		GroundCollisionCheck();
		
		return;
	}

	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == m_IsBossFight && true == IsBossRoomLeftOver())
		{
			return;
		}
		if (true == IsLeftOver())
		{
			return;
		}

		if (true == IsLeftWall())
		{
			return;
		}

		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			return;
		}

		Gravity(_DeltaTime);
		SetMove(float4::Left * m_DashSpeed * _DeltaTime); 
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
		    GetLevel()->SetCameraMove(float4::Left * m_DashSpeed * _DeltaTime);	
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
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

	const char* Dir = GetDirString().c_str();
	if (0 == strcmp(Dir, "Right_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_RightNormalAttackPos);
	}

	else if (0 == strcmp(Dir, "Left_"))
	{
		// ���� �������̶�� ���ϱ� �����ʿ� �浹ü �����
		m_SaberCollider->On();
		m_SaberCollider->SetPosition(m_LeftNormalAttackPos);
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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
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
		if (true == CameraPosCheck() && true != m_SpLevel->IsHeightSection() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}

		else if (true == m_SpLevel->IsSectionClear() && false == m_IsBossContact)
		{
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		}
	
		return;
	}
}

void Player_Zero::Jump_Attack_End()
{
	m_SaberCollider->Off();
}

void Player_Zero::Right_Wall_Start()
{
	m_WallSound = GameEngineResources::GetInst().SoundPlayToControl("player_wall_effect_sound.wav");
	m_WallSound.LoopCount(1);
	m_WallSound.Volume(0.2f);
	
	m_DirString = "Right_";
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

	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		if (true == GameEngineInput::IsPress("Jump"))
		{
			ChangeState(STATEVALUE::JUMP);
			return;
		}

		return;
	}

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

	m_DirString = "Left_";
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

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == GameEngineInput::IsPress("Jump"))
		{
			ChangeState(STATEVALUE::JUMP);
			return;
		}

		return;
	}


	// �Ʒ��� �������ٰ� �� ������ ���� �ƴϰ� �Ǵ� ���� ��
	if (false == IsLeftWall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	if (true == IsLeftWall() && true == GameEngineInput::IsDown("Jump"))
	{
		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			ChangeState(STATEVALUE::LEFT_WALL_JUMP);
			return;
		}
	}


	// �� ���� ���⼭ ����Ű�� ������ �ٷ� ĳ���Ͱ� �������� fall ���°� �Ǵϱ� ������ ������ �߾ȵȴ�. ��
	if (true == GameEngineInput::IsPress("Right_Move"))
	{		
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

void Player_Zero::RideUp_Start()
{
	AnimDirCheck("rideup_start");
}

void Player_Zero::RideUp_Update(float _DeltaTime)
{
	// ��ٸ��� Ÿ�� �ִ� ������ �� �浹���°� �����Ǹ� fall ���·� ����
	if (false == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_LADDER), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		if (true == IsGround())
		{
			ChangeState(STATEVALUE::IDLE);
			return;
		}
		
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// �ϴ� �ӽ÷� ��, ��Ű�� ���� ��� return; 
	if (true == GameEngineInput::IsPress("Right_Move") || true == GameEngineInput::IsPress("Left_Move"))
	{
		return; 
	}

	if (false == GameEngineInput::IsPress("Up_Move") && false == GameEngineInput::IsPress("Down_Move"))
	{
		AnimDirCheck("rideup_start");
		return;
	}

	if (true == GameEngineInput::IsPress("Up_Move"))
	{
		AnimDirCheck("rideup");
		SetMove(float4::Up * m_MoveSpeed * _DeltaTime);
		return;
	}

	if (true == GameEngineInput::IsPress("Down_Move"))
	{
		AnimDirCheck("rideup");
		SetMove(float4::Down * m_MoveSpeed * _DeltaTime);
		return;
	}
}

void Player_Zero::RideUp_End()
{
}

void Player_Zero::Door_Contact_Start()
{
	m_AnimationRender->ChangeAnimation("door_contact");
}

void Player_Zero::Door_Contact_Update(float _DeltaTime)
{
	// �浹�� ����Ǹ� ���̵�� �����̰� 
	if (false == m_Collider->Collision({ .TargetGroup = static_cast<int>(COLORDER::OBJECT_DOOR), .TargetColType = CT_Rect, .ThisColType = CT_Rect }))
	{
		// ���� �浹�� ���� �浹ü�� Death ��Ű�� �ʹ�.. �� 
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// ī�޶������ ���������� �̵�����. ���. 
	SetMove((float4::Right * m_DoorCol_MoveSpeed) * _DeltaTime);
	GetLevel()->SetCameraMove((float4::Right * m_DoorCol_MoveSpeed) * _DeltaTime);
}

void Player_Zero::Door_Contact_End()
{
}

void Player_Zero::Hit_Start()
{

	AnimDirCheck("Hit");
}

void Player_Zero::Hit_Update(float _DeltaTime)
{

	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	Gravity(_DeltaTime);
	GroundCollisionCheck();
}

void Player_Zero::Hit_End()
{
}
