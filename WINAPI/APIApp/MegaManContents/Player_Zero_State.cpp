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

// -----------------리콜 완료---------------------
void Player_Zero::Recall_Start()
{
	m_RecallSound = GameEngineResources::GetInst().SoundPlayToControl("player_recall_sound.wav");
	m_RecallSound.LoopCount(1);
	m_RecallSound.Volume(0.2f);
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


void Player_Zero::Idle_Start()
{
	// 방향체크 후 애니메이션 출력
	AnimDirCheck("Idle");
}

void Player_Zero::Idle_Update(float _DeltaTime)
{
	if (true == IsFall())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// 내가 지금 땅에 박혀 있는 상태라면 올려준다. 
	if (true == IsHitTheGround())
	{
		// 내가 바닥에 쳐박혀있다면 올려주어야함
		GroundCollisionCheck();
	}
	// 현재 나의 픽셀이 검은색 일때만
	if (RGB(0, 0, 0) == GetColor())
	{
		// 이동
		if (GameEngineInput::IsPress("Left_Move") || GameEngineInput::IsPress("Right_Move"))
		{
			ChangeState(STATEVALUE::MOVE);
			return;
		}
	}

	// 내가 땅에 있고, 점프키가 눌렸다면 점프상태로 변환
	if (true == IsGround() && true == GameEngineInput::IsDown("Jump"))
	{
		ChangeState(STATEVALUE::JUMP);
		return;
	}

	// 기본공격
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	// 대쉬
	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}
}

void Player_Zero::Idle_End()
{
}

// 이동시작시 방향+애니메이션체크
void Player_Zero::Move_Start()
{
	AnimDirCheck("Move");
}

void Player_Zero::Move_Update(float _DeltaTime)
{
	// 내가 땅에 박혀있으면 한번올려주고, 내가 땅이 아니면 fall 상태로 변경
	GroundCollisionCheck();
	if (true != IsGround())
	{
		ChangeState(STATEVALUE::FALL);
		return;
	}

	// 현재 아무키도 눌리지 않은 상태라면 IDLE 상태로 변경
	if (false == GameEngineInput::IsPress("Left_Move") &&
		false == GameEngineInput::IsPress("Right_Move"))
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// 현재 내가 땅에 있고, 점프키가 눌렸다면 점프상태로 변경
	if (true == IsGround() && true == GameEngineInput::IsPress("Jump"))
	{
		if (true == IsRightWall() || true == IsLeftWall())
		{
			return;
		}
		ChangeState(STATEVALUE::JUMP);
		return;
	}
	
	// 공격 
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::ATTACK_FIRST);
		return;
	}

	// 대쉬키가 눌렸다면 Dash 상태로 변경
	if (true == GameEngineInput::IsPress("Dash"))
	{
		ChangeState(STATEVALUE::DASH);
		return;
	}

	// 우측키가 눌려있다면 
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		// 우측키가 눌린상태에서 좌측키를 입력하면 return
		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			return;
		}

		// 우측키가 눌린상태에서 내 오른쪽이 벽이 아니라면 
		if (true != IsRightWall())
		{
			// 중력, 땅에 박혀있다면 꺼내주고 
			Gravity(_DeltaTime);
			GroundCollisionCheck();
			// 이동연산 + 카메라이동 해주고 
			SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);

			AnimDirCheck("Move");
			return;
		}

	}

	// 왼쪽무브
	if (true == GameEngineInput::IsPress("Left_Move"))
	{
		// 왼쪽못나가게 체크해주고
		if (true == IsLeftOver())
		{
			return;
		}

		// 왼쪽키가 눌린상태에서 우측키를 누르면 아무동작도 하지 않음
		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			return;
		}

		// 왼쪽이 벽이 아닐 경우에만 연산한다 
		if (true != IsLeftWall())
		{	
			Gravity(_DeltaTime);
			GroundCollisionCheck();
			SetMove(float4::Left * m_MoveSpeed * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);

			AnimDirCheck("Move");
			return;
		}
	}
}

// 일단 여기까지 임시 완료 -----------------------------------------------

void Player_Zero::Move_End()
{

}

// 쌤코드 점프스타트
//m_Jump = true;
//IsJumpMax = false;
//
//m_JumpPower = 50.0f;
//m_GravityPower = 800.0f;


// 쌤코드 점프업데이트
	//if (false == IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	//{
	//	// 키가 눌려있다면 점프파워를 계속 증가시킨다. 
	//	m_JumpPower += 500.0f * _DeltaTime;

	//	// 점프파워가 일정수치이상 넘어갔다면
	//	if (m_JumpPower >= 100.0f)
	//	{
	//		// 점프파워를 ?
	//		m_JumpPower = 100.0f;
	//		IsJumpMax = true;
	//	}
	// 
	//m_MoveDir += float4::Up * m_JumpPower;
	//m_JumpPower -= m_GravityPower * _DeltaTime;


void Player_Zero::Jump_Start()
{
	// 사운드출력
	m_JumpSound = GameEngineResources::GetInst().SoundPlayToControl("player_jump_sound.wav");
	m_JumpSound.LoopCount(1);
	m_JumpSound.Volume(0.2f);

	m_IsJumpMax = false;
	m_JumpPower = 50.0f;

	AnimDirCheck("Jump");
}

// 점프업데이트
void Player_Zero::Jump_Update(float _DeltaTime)
{
	// 업데이트에서 올려주는 작업을 안하면 어디서 해야하지
	// 내가만약 쳐박혀 있다면. 이라는 코드가 있고. 

	// 두번체크를함. 점프라는건 공중으로 뛰어오르는게 점프다. 
	// 일정 높이까지 올라갔으면 낙하로 상태가 변경되어야 하는가? 
	if (true == IsHitTheGround())
	{
		m_LandingSound = GameEngineResources::GetInst().SoundPlayToControl("player_landing_sound.wav");
		m_LandingSound.LoopCount(1);
		m_LandingSound.Volume(0.2f);

		GroundCollisionCheck();
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	// 점프상태에서 공격키를 입력하면 점프 공격 상태로 변경
	if (true == GameEngineInput::IsDown("Attack"))
	{
		ChangeState(STATEVALUE::JUMP_ATTACK);
		return;
	}

	// 점프키가 여전히 눌린상태라면 점프에 힘을 더해준다. 
	if (false == m_IsJumpMax && true == GameEngineInput::IsPress("Jump"))
	{
		// 눌린상태에서 키를 누를 수가 있나..? 
		if (true == GameEngineInput::IsDown("Jump"))
		{
			// 어떻게? 
			m_IsJumpMax = true;
			return;
		}
		
		// 키가 눌려있다면 점프파워를 계속 증가시킨다. 
		m_JumpPower += 60.0f;

		// 여기서 이전 상태가 대시였을 경우에는 점프맥스파워의 값을 조정하면 될 거 같은데. 
		// 점프파워가 일정수치이상 넘어갔다면
		if (m_JumpPower >= m_JumpPowerMax)
		{
			// 점프파워를 고정시키고 최대 점프위치에 도달
			m_JumpPower = m_JumpPowerMax;
			m_IsJumpMax = true;
		}
	}

	// 여기까지가 점프 계산식인데.
	m_JumpPower -= (m_GravityPower * 2.2f) * _DeltaTime;
	SetMove(float4::Up * m_JumpPower * _DeltaTime);
	
	// 내 오른쪽이 벽이 아닐때만	
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}

		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
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
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
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

// 낙하 업데이트 
// 낙하 임시완료 
void Player_Zero::Fall_Update(float _DeltaTime)
{
	// 낙하상태일 경우 중력연산
	Gravity(_DeltaTime);
	
	if (false == IsLeftWall() || false == IsRightWall())
	{
		GroundCollisionCheck();
	}

	// 내가 현재 땅이라면 아이들 상태로 변경해준다. 
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

	
	// 낙하중 우측이나 좌측방향키 입력시 그 방향으로 움직여준다. 
	if (true != IsRightWall() && true == GameEngineInput::IsPress("Right_Move"))
	{
		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
		AnimDirCheck("Fall_end");
		return;
	}

	if (true != IsLeftWall() && true == GameEngineInput::IsPress("Left_Move"))
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
	// 애니메이션이 끝나면 idle로 변경
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

	// 이동로직작성
	// 그냥이동이랑 똑같이하고 무브스피드를 대쉬스피드로 바꾸면 될 것 같다.  
	if (true == GameEngineInput::IsPress("Dash") && true == GameEngineInput::IsPress("Right_Move"))
	{
		// 우측 대시를 하는 도중 벽을 만나게 되면 
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
		GetLevel()->SetCameraMove(float4::Right * m_DashSpeed * _DeltaTime);
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

	// 내 오른쪽이 벽이 아닐때만	
	if (true == GameEngineInput::IsPress("Right_Move"))
	{
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}

		SetMove(float4::Right * m_MoveSpeed * _DeltaTime);
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
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
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);
		return;
	}
}

void Player_Zero::Jump_Attack_End()
{
}

void Player_Zero::Right_Wall_Start()
{
	AnimDirCheck("wall");
}

void Player_Zero::Right_Wall_Update(float _DeltaTime)
{
	// 그라운드 상태가 되면 IDLE상태로 변경
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}
	SetMove(float4::Down * (m_MoveSpeed* 0.5f) * _DeltaTime);

	// 아래로 내려가다가 내 오른쪽이 벽이 아니게 되는 순간 폴
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
		GetLevel()->SetCameraMove(float4::Left * m_MoveSpeed * _DeltaTime);

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
	// 만약 내 위가 벽인데 점프하려고 한다면
	// 나의 위치를 내려준다. 
	if (true == IsTopWall())
	{
		while (false == IsTopWall())
		{
			SetMove(float4::Down * _DeltaTime);
		}

		ChangeState(STATEVALUE::FALL);
		return;
	}

	// 애니메이션이 종료되었다면
	if (true == m_AnimationRender->IsAnimationEnd())
	{
		// 애니메이션이 종료된시점에 내오른쪽이 벽이라면 RIHGTWALL 
		if (true == IsRightWall())
		{
			ChangeState(STATEVALUE::RIGHT_WALL);
			return;
		}

		// 내가 낙하상태라면 FALL
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
	AnimDirCheck("wall");
}

void Player_Zero::Left_Wall_Update(float _DeltaTime)
{
	// 그라운드 상태가 되면 IDLE상태로 변경
	if (true == IsGround())
	{
		ChangeState(STATEVALUE::IDLE);
		return;
	}

	SetMove(float4::Down * (m_MoveSpeed * 0.5f) * _DeltaTime);

	// 아래로 내려가다가 내 왼쪽이 벽이 아니게 되는 순간 폴
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
		GetLevel()->SetCameraMove(float4::Right * m_MoveSpeed * _DeltaTime);
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
