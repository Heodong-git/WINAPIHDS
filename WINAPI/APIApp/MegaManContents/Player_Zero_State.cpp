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
	case PlayerState::JUMPATTACK:
		JumpAttackStart();
		break;
	case PlayerState::DASHATTACK:
		DashAttackStart();
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
	case PlayerState::JUMPATTACK:
		JumpAttackEnd();
		break;
	case PlayerState::DASHATTACK:
		DashAttackEnd();
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
	case PlayerState::JUMPATTACK:
		JumpAttackUpdate(_Time);
		break;
	case PlayerState::DASHATTACK:
		DashAttackUpdate(_Time);
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
	// 기본 상태의 업데이트에서는 특정키가 눌리면 
	// 원하는 상태에 맞게 상태를 변경해준다. 
	if (GameEngineInput::IsPress("LeftMove") || GameEngineInput::IsPress("RightMove")
		|| GameEngineInput::IsPress("UpMove") || GameEngineInput::IsPress("DownMove"))
	{
		ChangeState(PlayerState::MOVE);
		return; // 보통 스테이트를 체인지하면 아래 코드를 실행되면 
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

	// 키가 눌렸다면 해당하는 움직임 수행
	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		//AnimationRender->ChangeAnimation(DirString + "Move");
		SetMove(float4::Left * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Left * _Time * MoveSpeed);
	}
	else if (true == GameEngineInput::IsPress("RightMove"))
	{
		//AnimationRender->ChangeAnimation(DirString +"Move");
		SetMove(float4::Right * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Right * _Time * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress("UpMove"))
	{
		SetMove(float4::Up * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Up * _Time * MoveSpeed);
	}

	else if (true == GameEngineInput::IsPress("DownMove"))
	{
		//AnimationRender->ChangeAnimation(DirString +"Move");
		SetMove(float4::Down * MoveSpeed * _Time);
		GetLevel()->SetCameraMove(float4::Down * _Time * MoveSpeed);
	}

	// 왼쪽무브를 먼저체크하기 때문에 오른쪽키가 눌린상태에서는 왼쪽키를 눌러도 
	// if 문이 동작하여 반대로 이동 + 애니메이션이  출력되지만 왼쪽키가 눌린상태에서는
	// 오른쪽키를 눌러도 왼쪽방향체크가 먼저되어 아래 코드가 동작하지 않는 것 같다. 

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
}

void Player_Zero::JumpUpdate(float _Time)
{
}

void Player_Zero::JumpEnd()
{
}

void Player_Zero::JumpAttackStart()
{
}

void Player_Zero::JumpAttackUpdate(float _Time)
{
}

void Player_Zero::JumpAttackEnd()
{
}

void Player_Zero::DashStart()
{
}

void Player_Zero::DashUpdate(float _Time)
{
}

void Player_Zero::DashEnd()
{
}

void Player_Zero::DashAttackStart()
{
}

void Player_Zero::DashAttackUpdate(float _Time)
{
}

void Player_Zero::DashAttackEnd()
{
}
