#include "Player_Zero.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SpacePortLevel.h"

#include <GameEngineBase/GameEngineTime.h>

#include "ContentsEnum.h"

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

// 디버그용 무브 
void Player_Zero::DebugMove(float _DeltaTime)
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
	return;
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
	ColMapName = "ColMap_Spaceport.BMP";

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
}


// 상수들은 다 내가 변수로 만들어서 사용해야함. 생각할 것. 
void Player_Zero::Update(float _DeltaTime)
{
	// 디버그 키를 눌렀는지 체크는 위에서 해주어야 하니까 여기다가.
	if (true == GameEngineInput::IsDown("DebugMode"))
	{
		DebugSwitch();
		return;
	}
	// --------------------- 디버그용 이동 -----------------------------
	// 디버그 이동의 경우 이동하고 아무것도 수행하지 않아야함. 
	if (true == m_DebugMode)
	{
		DebugMove(_DeltaTime);
		return;
	}

	// 현재 플레이어의 상태값에 따라 업데이트를 진행.
	UpdateState(_DeltaTime);
}

// 땅체크
// 이게 지금 땅체크가 아니라 내가 박혀있는지? 로 변경해야될거 같은데
bool Player_Zero::IsHitTheGround(float4 Pos)
{	
	return (RGB(255, 255, 255) == GetColor()) && (RGB(255, 255, 255) == GetColor(float4::Down));
}

bool Player_Zero::IsGround(float4 Pos)
{
	// 내가 검은색이고, 내 아래가 흰색이면 땅위에 서있는거야. 그게아니면 false
	return (RGB(0, 0, 0) == GetColor()) && (RGB(255,255,255) == GetColor(float4::Down));
}

bool Player_Zero::IsFall(float4 Pos)
{
	return RGB(0, 0, 0) == GetColor() && RGB(0, 0, 0) == GetColor(float4::Down) && 
		   RGB(0, 0, 0) == GetColor(float4::Down + float4::Down);
}

// 왼쪽벽, 오른쪽벽을 다시 정의해
bool Player_Zero::IsRightWall(float4 Pos)
{
	if (RGB(0, 0, 0) == GetColor() && RGB(255, 255, 255) == GetColor(float4::Right) &&
		RGB(255, 255, 255) == GetColor(float4::Right + float4::Up) && 
		RGB(255,255,255) == GetColor(float4::Right + float4::Down))
	{
		return true;
	}

	return false;
}

bool Player_Zero::IsLeftWall(float4 Pos)
{
	if (RGB(0, 0, 0) == GetColor() && RGB(255, 255, 255) == GetColor(float4::Left) &&
		RGB(255,255,255) == GetColor(float4::Left + float4::Up) &&
		RGB(255, 255, 255) == GetColor(float4::Left + float4::Down))
	{
		return true;
	}

	return false;
}



// 테스트용
bool Player_Zero::IsLeftOver()
{
	float4 OverPos = m_StartPos;
	float4 NextPos = GetPos() + float4::Left;

	return OverPos.x > NextPos.x;
}


int Player_Zero::GetColor(float4 Pos)
{
	// 내 위치의 픽셀값을 기준으로 한 + 위치의 픽셀값을 받아온다. 
	// 델타타임을 곱한값으로 받아와야 하지 않나? 
	float4 CheckPos = GetPos() + (Pos * m_MoveSpeed * GameEngineTime::GlobalTime.GetFloatDeltaTime());

	// 상수는 안쓰는게 좋다. <-- 인지하고
	// 충돌맵이 없다면 assert 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
		return RGB(0,0,0);
	}

	ColorCheck CC;

	// 충돌맵이미지에서 해당하는 위치의 픽셀값을 받아서 리턴한다. 
	CC.Color = ColImage->GetPixelColor(CheckPos, RGB(255, 255, 255));

	// 디버그용 코드 
	bool Check = CC.Color == RGB(255, 255, 255);

	return CC.Color;
}

// 중력적용시 호출할 함수 
void Player_Zero::Gravity(float _DeltaTime)
{
	SetMove(float4::Down * m_GravityPower * _DeltaTime);
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

	// m_Collider->DebugRender();
	// 디버그용 위치출력시 참고할 코드 
	std::string PlayerText = "PlayerPosition : ";
	PlayerText += GetPos().ToString();

	/*std::string CameraMouseText = "MousePositionCamera : ";
	CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();*/

	GameEngineLevel::DebugTextPush(PlayerText);
	// GameEngineLevel::DebugTextPush(CameraMouseText);
}


void Player_Zero::GroundCollisionCheck(float4 _Pos)
{
	// 땅에쳐박혀있다면 올려준다.  
	while (IsHitTheGround(_Pos))
	{
		SetMove(float4::Up);
	}	
}


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
									   .Start = 19 , .End = 30 , .InterTime = 0.07f , .Loop = false });

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
									   .Start = 19 , .End = 30 , .InterTime = 0.07f , .Loop = false });

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
