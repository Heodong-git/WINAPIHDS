#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "ContentsEnum.h"


// 상태변경 함수
void Player_Zero::ChangeState(STATEVALUE _State)
{
	// 플레이어의 다음 상태를 받아온다. 
	m_NextState = _State;
	// 플레이어의 이전 상태는 현재 상태가 된다. 
	m_PrevState = m_StateValue;
	// 현재 상태를 변경될 상태로 변경한다. 
	m_StateValue = m_NextState;

	// 다음 상태값이 무엇이냐에 따라서 Start 함수 호출
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
	}

	// 다음 상태의 Start 함수를 호출 한 이후에 
	// 이전 상태의 End 함수를 호출하여 마무리 작업을 수행한다. 
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
	}
}

void Player_Zero::UpdateState(float _DeltaTime)
{
	// 현재 상태값에 따라서 분기처리
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
	}
}

// -----------------리콜 완료---------------------
void Player_Zero::Recall_Start()
{
	// 플레이어 방향체크 + 애니메이션 출력
	AnimDirCheck("recall");
}

void Player_Zero::Recall_Update(float _DeltaTime)
{
	// 애니메이션이 종료 되었다면 아이들로 전환
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return; 
	}
}

void Player_Zero::Recall_End()
{
}


// 
void Player_Zero::Idle_Start()
{
	// 방향체크 후 애니메이션 출력
	AnimDirCheck("Idle");
}

void Player_Zero::Idle_Update(float _DeltaTime)
{
	if (GameEngineInput::IsPress("Left_Move") || GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::MOVE);
		return;
	}

	// 내 현재 위치가 땅이야
	if (true == IsGround())
	{
		// 내가 바닥에 쳐박혀있다면 올려주어야함
		GroundCollisionCheck();
		return;
	}

	if (true == IsFall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// 아이들 상태에서 점프 버튼 한번 눌렸다면 점프 상태로 전환한다. 
	if (true == GameEngineInput::IsPress("Jump"))
	{
		// ChangeState(STATEVALUE::JUMP);
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
	// 좌우키가 눌린 상태가 아니라면 아이들로 전환
	if (false == GameEngineInput::IsPress("Left_Move") &&
		false == GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	if (true == GameEngineInput::IsPress("Jump"))
	{
		// ChangeState(STATEVALUE::JUMP);
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
		Gravity(_DeltaTime);
		SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		GroundCollisionCheck();
		if (true == IsFall())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}
		AnimDirCheck("Move");
		return;
	}

	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		Gravity(_DeltaTime);
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GroundCollisionCheck();
		if (true == IsFall())
		{
			ChangeState(STATEVALUE::FALL);
			return;
		}
		AnimDirCheck("Move");
		return;
	}
}

void Player_Zero::Move_End()
{

}

void Player_Zero::Jump_Start()
{
	// 해근샘 
	// 점프상태를 true 
	m_Jump = true;
	IsJumpMax = false;

	// 점프가 시작되면 기본 점프파워를 30으로.
	m_JumpPower = 50.0f;
	m_GravityPower = 800.0f;

	AnimDirCheck("Jump");
}

void Player_Zero::Jump_Update(float _DeltaTime)
{
	// 현재 점프가 최대높이가 아니고, 점프키가 눌려있다면 동작
	if (false == IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	{
		// 키가 눌려있다면 점프파워를 계속 증가시킨다. 
		m_JumpPower += 500.0f * _DeltaTime;

		// 점프파워가 일정수치이상 넘어갔다면
		if (m_JumpPower >= 100.0f)
		{
			// 점프파워를 ?
			m_JumpPower = 100.0f;
			IsJumpMax = true;
		}
	}

	m_MoveDir += float4::Up * m_JumpPower;
	m_JumpPower -= m_GravityPower * _DeltaTime;
}

void Player_Zero::Jump_End()
{
	m_Jump = false;
	ChangeState(STATEVALUE::IDLE);
}

void Player_Zero::Fall_Start()
{
	AnimDirCheck("Fall");
}

// 낙하 업데이트에서 체크해야할 것
void Player_Zero::Fall_Update(float _DeltaTime)
{
	Gravity(_DeltaTime);
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
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
}

void Player_Zero::Attack_First_Start()
{
	AnimDirCheck("normal_attack_first");
}

void Player_Zero::Attack_First_Update(float _Time)
{
	// 공격의 마지막 프레임에 도달하면 Idle 상태로 변경해준다. 
	// 일단 임시로 적용해두고, 나중에 만들때 노말어택 1타, 23타 상태로 구분해서 적용한다. 
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// 1타 모션이 끝나지 않은 상태에서 X 키를 한번 더 누르면 2타진행
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

	// 이동로직작성
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
