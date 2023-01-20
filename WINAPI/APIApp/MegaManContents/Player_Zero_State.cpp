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
	PlayerState NextState = _State;
	// 플레이어의 이전 상태는 현재 상태가 된다. 
	PlayerState PrevState = StateValue;
	// 현재 상태를 변경될 상태로 변경한다. 
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
	default:
		break;
	}

	// 종료될 상태에 따라서 그 상태의 End 함수를 호출
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
	default:
		break;
	}
}

// 상태업데이트 
void Player_Zero::UpdateState(float _Time)
{
	// 현재 상태값에 따라서 분기처리
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
	
	// Idle 상태일 경우 왼쪽, 오른쪽 키가 눌렸다면 Move 상태로 변경한다.  
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove"))
	{
		ChangeState(PlayerState::MOVE);
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

void Player_Zero::MoveUpdate(float _Time)
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

	if (true == GameEngineInput::IsPress("Dash"))
	{
		// ChangeState(PlayerState::DASH);
		// GetLevel()->SetCameraMove(float4::Up * _Time * MoveSpeed * 2.0f);
	}

	// 키가 눌렸다면 해당하는 움직임 수행
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		MoveDir += float4::Left * MoveSpeed;
		//GetLevel()->SetCameraMove(float4::Left * _Time * MoveSpeed);
	}
	
	if (true == GameEngineInput::IsPress("RightMove"))
	{
		MoveDir += float4::Right * MoveSpeed;
		//GetLevel()->SetCameraMove(float4::Right * _Time * MoveSpeed);
	}

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
	Jump = true;
	PrevPos = GetPos();
	DirCheck("Move");
}

void Player_Zero::JumpUpdate(float _Time)
{
	AnimationRender->ChangeAnimation(DirString + "Dash");
	
	// 이전좌표값을 구해놨고, 점프했을 때 의 y축 좌표랑 
	// 그전 y 축 좌표를 뺐을때 의 값이 200이상 차이나면
	// 이전 좌표는 초기화, 낙하상태로만듬 , 200은 점프높이. 
	/*if (200 <= abs(PrevPos.y - GetPos().y))
	{
		PrevPos = float4::Zero;
		ChangeState(PlayerState::IDLE);
		return;
	}*/

	//MoveDir += float4::Up* MoveSpeed * JumpPower * _Time;
		
}

void Player_Zero::JumpEnd()
{
	
}

void Player_Zero::FallStart()
{
	DirCheck("Move");
}

void Player_Zero::FallUpdate(float _DeltaTime)
{
	// 낙하업데이트, 
}

void Player_Zero::FallEnd()
{
}

void Player_Zero::DashStart()
{
	DirCheck("Dash");
}

void Player_Zero::DashUpdate(float _Time)
{
}

void Player_Zero::DashEnd()
{
}

