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
	case PlayerState::JUMPATTACK:
		JumpAttackStart();
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

// 상태업데이트 
void Player_Zero::UpdateState(float _DeltaTime)
{
	// 현재 상태값에 따라서 분기처리
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
	// 단일 충돌체크 
	if (true == m_Collision->Collision({ .TargetGroup = static_cast<int>(COLORDER::MONSTER) }))
	{
		ChangeState(PlayerState::HIT);
		return;
	}


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


// 그냥 ㅅㅂ 클래스 따로 만들면 바로 해결일거 같은데
// 클래스 만들고, 대쉬스타트하면 생성, 클래스 자체 업데이트에서는 시간지나면 데스
// 데스처리한거는 오늘 릴리즈구조 만들었으니까 
void Player_Zero::DashStart()
{
	// 대시 스타트에서는 이펙트렌더러의 업데이트상태를 on으로 변경
	DirCheck("Dash");
	if (true == GameEngineInput::IsPress("RightMove"))
	{
		m_EffectRender->SetPosition(float4{ -250 , 0 });
		m_EffectRender->ChangeAnimation(m_DirString + "dash_effect");
	}

	if (true == GameEngineInput::IsPress("LeftMove"))
	{
		m_EffectRender->SetPosition(float4{ 250 , 0 });
		m_EffectRender->ChangeAnimation(m_DirString + "dash_effect");
	}
}

void Player_Zero::DashUpdate(float _Time)
{
	// 대쉬업데이트에서는 공중상태에서 대쉬 모션이 종료되면 
	// 낙하모션으로 바뀌어야함. 결국 그냥 낙하모션을 따로 해야되네 
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
	// 지금 쳐맞는 중일 때는 맞고나서 애니메이션이 끝날때 까지는 무적이어야함.
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
	// 점프키 중에 반대방향키를 누르면 그쪽으로 애니메이션이 바뀌어야함. 
	if (true == GameEngineInput::IsPress("LeftMove") || true == GameEngineInput::IsPress("RightMove"))
	{
		// 어.. 음.. 흠.. 흐음.. 일단 나중에 다른 애니메이션부터.. 
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
	// 나중에 땅을 밟은상태인지 아닌지를 추가해서 다시 ㄱㄱ
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
	// 앉기 키가 계속 눌려있었다면
	if (true == GameEngineInput::IsPress("Sit"))
	{
		// 완전히 앉아있는 애니메이션을 유지하고
		DirCheck("press_sit");

		// 앉은 상태에서 공격키를 눌렀다면 앉은공격 상태로 변경인데. 
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


