#include "Player_Zero.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpacePortLevel.h"

#include "ContentsEnum.h"

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

void Player_Zero::AnimDirCheck(const std::string_view& _AnimationName)
{
	// 현재 방향문자열 값을 받아온다. 
	std::string PrevDirString = m_DirString;
	// 해당하는 방향의 애니메이션으로 change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	
	// 만약 leftmove 키가 눌렸다면
	if (GameEngineInput::IsPress("Left_Move"))
	{
		// 현재 방향문자열을 left_ 로 변경한다. 
		m_DirString = "Left_";
	}
	// 만약 rightmove 키가 눌렸다면 
	else if (GameEngineInput::IsPress("Right_Move"))
	{
		// 현재 방향문자열을 right_ 로 변경한다.
		m_DirString = "Right_";
	}

	// 변경 이후 
	// 만약 이전 방향문자열이 현재 방향문자열과 다르다면
	if (PrevDirString != m_DirString)
	{
		m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	}
}

void Player_Zero::Start()
{
	if (false == GameEngineInput::IsKey("Left_Move"))
	{
		GameEngineInput::CreateKey("Left_Move", VK_LEFT);
		GameEngineInput::CreateKey("Right_Move", VK_RIGHT);
		GameEngineInput::CreateKey("Up_Move", VK_UP);
		GameEngineInput::CreateKey("Sit", VK_DOWN);
		GameEngineInput::CreateKey("Down_Move", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'C');
		GameEngineInput::CreateKey("Jump", 'X');
		GameEngineInput::CreateKey("DebugMode", 'Q');
	}

	// 렌더러생성, 생성시 zorder 값 입력 
	m_AnimationRender = CreateRender(ZORDER::PLAYER);
	m_AnimationRender->SetScale({ 1280 , 960 });

	// 애니메이션 생성
	PlayerCreateAnimation();

	// 플레이어 컬라이더
	m_Collider = CreateCollision(COLORDER::PLAYER);
	m_Collider->SetScale({ 150, 150 });
	m_Collider->SetDebugRenderType(CT_Rect);
	m_Collider->SetPosition(float4{ 0, -80 });

	// 여기서부터 다시
	// 빔샤벨 컬라이더
	m_SaberCollider = CreateCollision(COLORDER::PLAYERATTACK);
	
	
	// 확인해야함 여기서 리콜이면 
	ChangeState(STATEVALUE::RECALL);
}

void Player_Zero::Movecalculation(float _DeltaTime)
{
	// ---------------------디버그용 -----------------------------
	if (true == m_DebugMode)
	{
		if (true == GameEngineInput::IsPress("Left_Move"))
		{
			SetMove(float4::Left * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("Right_Move"))
		{
			SetMove(float4::Right * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("Up_Move"))
		{
			SetMove(float4::Up * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("Down_Move"))
		{
			SetMove(float4::Down * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Down * 3000.0f * _DeltaTime);
		}
		
		// 디버그용
		// 현재위치 체크
		float4 CurPos = GetPos();
		return;
	}

	// ---------------------실제  게임 플레이용 ---------------------------- 

	if (true == m_Gravity)
	{
		if (true == m_Jump)
		{
			m_MoveDir += float4::Down * (m_GravityPower * 1.5f ) * _DeltaTime;
		}

		else
		{
			// 중력 , 계속 아래로 떨어지는 힘이 더해진다 
			m_MoveDir += float4::Down * m_GravityPower * _DeltaTime;
		}
	
	}

	// 플레이어 속력 제한
	if (m_MoveSpeed <= abs(m_MoveDir.x))
	{
		
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -m_MoveSpeed;
		}
		else 
		{
			m_MoveDir.x = m_MoveSpeed;
		}
	}

	// 마찰력 , 나중에 값 조정
	if (false == GameEngineInput::IsPress("Left_Move") && false == GameEngineInput::IsPress("Right_Move"))
	{
		m_MoveDir.x *= 0.001f;
	}

	// 임시로 배경으로 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColMap_Spaceport.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	// 충돌체크 변수  
	bool Check = true;
	// 다음 이동위치 계산
	float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;

	// 다음 이동위치의 픽셀 값이 255, 0 , 255 라면 충돌한 것이다. 
	if (RGB(255, 0, 255) == ColImage->GetPixelColor(NextPos, RGB(255, 0, 255)))
	{
		Check = false;
		m_MoveDir = float4::Zero;
	}

	if (false == Check)
	{
		while (true)
		{
			m_MoveDir.y -= 1;

			float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;

			if (RGB(255, 0, 255) == ColImage->GetPixelColor(NextPos, RGB(255, 0, 255)))
			{
				continue;
			}

			break;
		}	
	}

	// 카메라는 X축이 더해지거나 Y축이 감소되는게 아니라면 움직이지 않는다.
	SpacePortLevel* PlayLevel = dynamic_cast<SpacePortLevel*>(GetLevel());

	if (nullptr == PlayLevel)
	{
		MsgAssert("받아온 레벨이 SpacePort 레벨이 아닙니다.");
		return;
	}

	// 플레이어의 이전 위치는 현재 위치.
	float4 PrevPos = GetPos();
	// 다음 위치는 이전위치 + 이동방향 * DeltaTime; 
	float4 PlayerNextPos = PrevPos + m_MoveDir * _DeltaTime;
	// 플레이어는 처음에 생성된 위치보다 뒤로는 못가
	if (PlayLevel->GetStatingPos().x > PlayerNextPos.x)
	{
		// 다시 기존위치로
		SetPos(PrevPos);
		return;
	}

	// 카메라 제한위치 받아오기. 
	float4 limitCameraPos = PlayLevel->GetStartCameraPos();
	// 현재 카메라 위치를 받아오고. 
	float4 CurCameraPos = GetLevel()->GetCameraPos();

	// 플레이어를 움직이고.
	SetMove(m_MoveDir * _DeltaTime);

	// 현재카메라위치 받아오고
	float4 PrevCameraPos = GetLevel()->GetCameraPos();
	// 다음위치는 지금위치 + 이동방향 
	float4 NextCameraPos = PrevCameraPos + m_MoveDir * _DeltaTime;

	// 카메라 움직여. 
	// 카메라가 플레이어를 처음부터 따라가지 않음
	// 플레이어의 위치가 윈도우x 하프 값보다 커질때부터 따라감
	if (GameEngineWindow::GetScreenSize().half().x <= GetPos().x)
	{
		GetLevel()->SetCameraMove(m_MoveDir *_DeltaTime);
	}

	if (NextCameraPos.x < limitCameraPos.x || NextCameraPos.y > limitCameraPos.y )
	{
		// 제한된 위치로 고정
		GetLevel()->SetCameraPos(PrevCameraPos);
		return;
	}
}

// 상수들은 다 내가 변수로 만들어서 사용해야함. 생각할 것. 
void Player_Zero::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("DebugMode"))
	{
		DebugSwitch();
	}
	// 현재 플레이어의 상태값에 따라 업데이트를 진행.
	UpdateState(_DeltaTime);
	
	Movecalculation(_DeltaTime);

	// 컬리전삭제 예시용코드 
	/*if (nullptr != BodyCollision)
	{
		std::vector<GameEngineCollision*> Collision;
		if (true == BodyCollision->Collision({ .TargetGroup = static_cast<int>(BubbleCollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect }, Collision))
		{
			for (size_t i = 0; i < Collision.size(); i++)
			{
				GameEngineActor* ColActor = Collision[i]->GetActor();
				ColActor->Death();
			}
		}
	}*/
	
}

// 오브젝트의 중심점을 알 수 있도록 사각형 출력 
void Player_Zero::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() -GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);


	//m_Collision->DebugRender();
	
	
	// 디버그용 위치출력시 참고할 코드 
	/*std::string MouseText = "MousePosition : ";
	MouseText += GetLevel()->GetMousePos().ToString();

	std::string CameraMouseText = "MousePositionCamera : ";
	CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();

	GameEngineLevel::DebugTextPush(MouseText);
	GameEngineLevel::DebugTextPush(CameraMouseText);*/
}

void Player_Zero::PlayerCreateAnimation()
{
	// 리콜
	// 0 ~ 18
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_recall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.075f });
	// 오른쪽 아이들
	// 14 ~ 18
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 14 , .End = 18 , .InterTime = 0.14f });

	// 근데 점프는 누르면 누를수록 더 높이 올라가는데 애니메이션 다만들고 생각.
	// 오른쪽 점프
	// 19 ~ 31 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 19 , .End = 22 , .InterTime = 0.1f , .Loop = false });

	// 오른쪽 fall 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_fall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 23 , .End = 30 , .InterTime = 0.03f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_fall_end" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 30 , .End = 30 , .InterTime = 0.001f , .Loop = false });


	// 31~32 착지모션인데 일단. 음..일단 만들어둬 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_landing" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 30 , .End = 32 , .InterTime = 0.4f });


	// 오른쪽 무브
	// 37 ~ 50
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 37 , .End = 50 , .InterTime = 0.04f });
	// 오른쪽 공격
	// 51~91 까지 1~3타
	// 1타 : 51 ~ 66 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_first" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 51 , .End = 66 , .InterTime = 0.025f });
	// 2타 67 ~ 78
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_second" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 67 , .End = 78 , .InterTime = 0.025f });

	// 3타 79 ~ 92
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_third" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 79 , .End = 92 , .InterTime = 0.025f });

	// 오른쪽 점프공격 93 ~ 101
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 93 , .End = 101 , .InterTime = 0.03f });

	// 오른쪽 대쉬 111 ~ 121 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_dash" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 111 , .End = 121 , .InterTime = 0.05f });

	// 오른쪽 벽타는 모션
	// 122~126
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 122 , .End = 126 , .InterTime = 0.5f , .Loop = false });

	// 오른쪽 벽타기 중 점프
	// 127 ~ 129 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall_jump" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 127 , .End = 129 , .InterTime = 0.07f , .Loop = false });

	// 오른쪽 벽타기 중 공격 
	// 130 ~ 138 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 130 , .End = 138 , .InterTime = 0.05f , .Loop = false });

	// 힘들다 ㅠ 
	// 사다리 타기
	// 139 ~ 148 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 139 , .End = 148 , .InterTime = 0.06f });

	// 사다리 마지막에  올라가는 모션
	// 149 ~ 152 
	// 나중에 다시 손봐야 할 수도. 픽셀 살짝 애매함
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup_end" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 149 , .End = 152 , .InterTime = 0.07f });

	// 사다리 타는중 공격 
	// 153 ~ 161
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 153 , .End = 161 , .InterTime = 0.05f });

	// 오른쪽 피격
	// 162 ~ 165
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_hit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 162 , .End = 165 , .InterTime = 0.14f });

	// 일정체력 이하 아이들
	// 166 ~ 169
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle_tiring" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 166 , .End = 169 , .InterTime = 1.0f });

	// 쎄게 피격
	// 170 ~ 176
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_big_hit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 170 , .End = 176 , .InterTime = 0.15f });

	// exit 
	// 177 ~ 189
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_exit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 177 , .End = 189 , .InterTime = 0.09f });

	// ---------------------------------- 왼쪽 ---------------------------------------------



	// 왼쪽 리콜
	// 0 ~ 18 ,  0.075
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_recall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.075f });
	// 왼쪽 아이들
	// 14 ~ 18 , 0.14
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 14 , .End = 18 , .InterTime = 0.14f });

	// 근데 점프는 누르면 누를수록 더 높이 올라가는데 애니메이션 다만들고 생각.
	// 왼쪽 점프
	// 19 ~ 31 , 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 19 , .End = 25 , .InterTime = 0.1f });

	// 왼쪽 낙하
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_fall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 26 , .End = 30 , .InterTime = 0.03f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "left_fall_end" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 30 , .End = 30 , .InterTime = 0.001f , .Loop = false });


	// 31~32 착지모션인데 일단. 음..일단 만들어둬 
	// 30 ~ 32 ? 0.4
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_landing" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 30 , .End = 32 , .InterTime = 0.4f });


	// 왼쪽 무브
	// 37 ~ 50
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 37 , .End = 50 , .InterTime = 0.04f });
	// 왼쪽 공격
	// 51~91 까지 1~3타
	// 1타 : 51 ~ 66 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_first" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 51 , .End = 66, .InterTime = 0.025f });
	// 2타 67 ~ 78 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_second" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 67 , .End = 78 , .InterTime = 0.025f });

	// 3타 79 ~ 92 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_third" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 79 , .End = 92 , .InterTime = 0.025f });

	// 왼쪽 점프공격 93 ~ 101
	// 깔끔한거같은데
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 93 , .End = 101 , .InterTime = 0.03f });

	// 왼쪽 대쉬 111 ~ 121 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 111 , .End = 121 , .InterTime = 0.05f });

	// 오른쪽 벽타는 모션
	// 122~126
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 122 , .End = 126 , .InterTime = 0.5f , .Loop = false });

	// 오른쪽 벽타기 중 점프
	// 127 ~ 129 0.07
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall_jump" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 126 , .End = 129 , .InterTime = 0.07f , .Loop = false });

	// 오른쪽 벽타기 중 공격 
	// 130 ~ 138 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 130 , .End = 138 , .InterTime = 0.04f , .Loop = false });

	// 힘들다 ㅠ 
	// 사다리 타기
	// 139 ~ 148 0.06
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 139 , .End = 148 , .InterTime = 0.06f });

	// 사다리 마지막에  올라가는 모션
	// 149 ~ 152 
	// 나중에 다시 손봐야 할 수도. 픽셀 살짝 애매함
	// 이건 나중에 다시 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup_end" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 149 , .End = 152 , .InterTime = 0.07f });

	// 사다리 타는중 공격 
	// 153 ~ 161 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 153 , .End = 161 , .InterTime = 0.05f });

	// 왼쪽 피격
	// 162 ~ 165 0.14
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_hit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 162 , .End = 165 , .InterTime = 0.014f });

	// 일정체력 이하 아이들
	// 166 ~ 169 1.0
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle_tiring" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 166 , .End = 169 , .InterTime = 1.0f });

	// 쎄게 피격
	// 170 ~ 176 0.15
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_big_hit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 170 , .End = 175 , .InterTime = 0.15f });

	// exit 
	// 177 ~ 189 0.09
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_exit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 177 , .End = 189 , .InterTime = 0.09f });
}
