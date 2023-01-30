#include "Player_Zero.h"

#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"


// 상태변경 함수
void Player_Zero::ChangeState(PlayerState _State)
{
	// 플레이어의 다음 상태를 받아온다. 
	m_NextState = _State;
	// 플레이어의 이전 상태는 현재 상태가 된다. 
	m_PrevState = m_StateValue;
	// 현재 상태를 변경될 상태로 변경한다. 
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
	default:
		break;
	}

	// 종료될 상태에 따라서 그 상태의 End 함수를 호출
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
	default:
		break;
	}
}

// 상태업데이트 
void Player_Zero::UpdateState(float _Time)
{
	// 현재 상태값에 따라서 분기처리
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
	case PlayerState::SIT:
		SitUpdate(_Time);
		break;
	case PlayerState::SITATTACK:
		SitAttackUpdate(_Time);
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

	// 애니메이션 동작중에 왼쪽, 오른쪽키가 눌리면 아무것도 수행하지 않도록 예외처리
	if (true == GameEngineInput::IsPress("LeftMove") || true == GameEngineInput::IsPress("RightMove"))
	{
		return;
	}
	// 리콜의 업데이트에서는 애니메이션 재생이 완료 됐다면 아이들 상태로 전환한다. 
	// 재생완료 기준은 프레임을 확인하여 마지막 프레임에 도달했다면 , 아이들로 전환
	// 어.. 근데 왜 리콜스타트에서 애니메이션 변경이 안되지 , 코드파악 좀더 필요 
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

	// Idle 상태일 경우 왼쪽, 오른쪽 키가 눌렸다면 Move 상태로 변경한다.  
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
	// 무브의 업데이트에서는 현재 아무키도 눌리지 않았다면 기본 IDLE 상태로 변경한다.  
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

	// 키가 눌렸다면 해당하는 움직임 수행
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

	// 공격키가 눌렸다면 공격 
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

	if (GameEngineInput::IsPress("Sit"))
	{
		ChangeState(PlayerState::SIT);
		return;
	}

	DirCheck("Move");
}



void Player_Zero::MoveEnd()
{
}

// 일반공격 
void Player_Zero::NormalAttackStart()
{
	DirCheck("normal_attack");
}

void Player_Zero::NormalAttackUpdate(float _Time)
{
	// 공격의 마지막 프레임에 도달하면 Idle 상태로 변경해준다. 
	// 일단 임시로 적용해두고, 나중에 만들때 노말어택 1타, 23타 상태로 구분해서 적용한다. 
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
	if (m_AnimationRender->IsAnimationEnd())
	{
		ChangeState(PlayerState::IDLE);
		return;
	}
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

void Player_Zero::SitStart()
{
	DirCheck("Sit");
}
void Player_Zero::SitUpdate(float _DeltaTime)
{
	// 앉기 키가 계속 눌려있었다면
	if (true == GameEngineInput::IsPress("Sit"))
	{
		// 애니메이션을 그대로 유지
		DirCheck("Sit");

		// 앉은 상태에서 공격키를 눌렀다면 앉은공격 상태로 변경
		if (true == GameEngineInput::IsDown("Attack"))
		{
			ChangeState(PlayerState::SITATTACK);
		}

		return;
	}

	// 키가 눌려있지 않았다면 IDLE 상태로 전환 
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
	// 방향체크후 애니메이션 실행
	DirCheck("Sit_Attack");
}

void Player_Zero::SitAttackUpdate(float _DeltaTime)
{
	// 앉은 공격 애니메이션이 재생완료 되었다면
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// SIT 상태로 전환
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


