#include "Player_Zero.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

float Player_Zero::m_Time = 0.0f;

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}


void Player_Zero::DirCheck(const std::string_view& _AnimationName)
{
	// 현재 방향문자열 값을 받아온다. 
	std::string PrevDirString = m_DirString;
	// 해당하는 방향의 애니메이션으로 change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	
	// 만약 leftmove 키가 눌렸다면
	if (GameEngineInput::IsPress("LeftMove"))
	{
		// 현재 방향문자열을 left_ 로 변경한다. 
		m_DirString = "Left_";
	}
	// 만약 rightmove 키가 눌렸다면 
	else if (GameEngineInput::IsPress("RightMove"))
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
	// 플레이어의 위치

	// 키생성
	// 문자열을 키값으로 하여 원하는 키와 
	if (false == GameEngineInput::IsKey("LeftMove"))
	{
		GameEngineInput::CreateKey("LeftMove", VK_LEFT);
		GameEngineInput::CreateKey("RightMove", VK_RIGHT);
		GameEngineInput::CreateKey("UpMove", VK_UP);
		GameEngineInput::CreateKey("Sit", VK_DOWN);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
		GameEngineInput::CreateKey("DebugMode", 'Q');
	}


	// 렌더러생성, 생성시 zorder 값 입력 
	m_AnimationRender = CreateRender(ZORDER::PLAYER);
	m_AnimationRender->SetScale({ 640 * 1.1f , 480 * 1.6f });

	// 이펙트렌더러 생성
	m_EffectRender = CreateRender("effect_dash_right.bmp", ZORDER::PLAYER_EFFECT);
	m_EffectRender->SetScale({ 320 * 1.5f, 240 * 1.5f });

	// 이펙트애니메이션 생성
	m_EffectRender->CreateAnimation({ .AnimationName = "right_dash_effect" , .ImageName = "effect_dash_right.bmp" ,
								   . Start = 0, .End = 7, .InterTime = 0.05f });
	m_EffectRender->CreateAnimation({ .AnimationName = "left_dash_effect" , .ImageName = "effect_dash_left.bmp" ,
									   . Start = 0, .End = 7, .InterTime = 0.05f });

	// 충돌체 생성
	m_Collision = CreateCollision(COLORDER::PLAYER);
	m_Collision->SetScale({ 100 , 100 });

	// 플레이어
	// 리콜
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_recall" , .ImageName = "player_recall.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.07f });

	// 아이들
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.15f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.15f });

	// 좌우 무브
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });

	// 좌우 기본공격
	// 임시로 3타 묶어둠.
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack", .ImageName = "player_normal_attack_right.bmp" ,
									   .Start = 0, .End = 28, .InterTime = 0.025f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack" , .ImageName = "player_normal_attack_left.bmp" ,
									   .Start = 0, .End = 28 , .InterTime = 0.025f , .Loop = false });

	// 좌우 대쉬 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_dash", .ImageName = "player_doublejump_dash_sitattack_right.bmp" ,
								   .Start = 10, .End = 22, .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash" , .ImageName = "player_doublejump_dash_sitattack_left.bmp" ,
									   .Start = 10, .End = 22 , .InterTime = 0.06f , .Loop = false });

	// 좌우 앉기
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_sit", .ImageName = "player_doublejump_dash_sitattack_right.bmp" ,
								   .Start = 23, .End = 24, .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_sit" , .ImageName = "player_doublejump_dash_sitattack_left.bmp" ,
									   .Start = 23, .End = 24 , .InterTime = 0.05f , .Loop = false });

	// 앉기 유지시 출력할 이미지 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_press_sit", .ImageName = "player_doublejump_dash_sitattack_right.bmp" ,
								   .Start = 24, .End = 24, .InterTime = 0.1f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_press_sit" , .ImageName = "player_doublejump_dash_sitattack_left.bmp" ,
									   .Start = 24, .End = 24 , .InterTime = 0.1f , .Loop = false });

	// 앉기 공격
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_sit_attack", .ImageName = "player_doublejump_dash_sitattack_right.bmp" ,
								   .Start = 25, .End = 33, .InterTime = 0.04f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_sit_attack" , .ImageName = "player_doublejump_dash_sitattack_left.bmp" ,
									   .Start = 25, .End = 33 , .InterTime = 0.04f , .Loop = false });

	// 필요 없어보이지만 혹시 모르니 일단 남겨두고 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move_start",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move_start",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });

	// 더블점프 애니메이션
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_double_jump", .ImageName = "player_doublejump_dash_sitattack_right.bmp" ,
								   .Start = 0, .End = 9, .InterTime = 0.05f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_double_jump" , .ImageName = "player_doublejump_dash_sitattack_left.bmp" ,
									   .Start = 0, .End = 9 , .InterTime = 0.05f , .Loop = false });

	// 일반점프 애니메이션
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump", .ImageName = "player_jump_jumpattack_right.bmp" ,
								   .Start = 0, .End = 13, .InterTime = 0.08f , .Loop = true });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump" , .ImageName = "player_jump_jumpattack_left.bmp" ,
									   .Start = 0, .End = 13 , .InterTime = 0.08f , .Loop = true });

	// 점프 공격 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump_attack", .ImageName = "player_jump_jumpattack_right.bmp" ,
								   .Start = 15, .End = 23, .InterTime = 0.06f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump_attack" , .ImageName = "player_jump_jumpattack_left.bmp" ,
									   .Start = 15, .End = 23 , .InterTime = 0.06f , .Loop = false });

	// 히트 시 애니메이션
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_player_hit", .ImageName = "player_rope_attacked_right.bmp" ,
							   .Start = 20, .End = 23, .InterTime = 0.15f , .Loop = false });
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_player_hit" , .ImageName = "player_rope_attacked_left.bmp" ,
									   .Start = 20, .End = 23 , .InterTime = 0.15f , .Loop = false });
	/*m_HpBarRender = CreateRender(ZORDER::UI);
	m_HpBarRender->SetScale({ 320 * 3.0f , 240 * 3.0f });
	m_HpBarRender->CreateAnimation({ .AnimationName = "Player_Hpbar0" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 0 , .InterTime = 0.15f });

	m_HpBarRender->ChangeAnimation("Player_Hpbar0");*/
	
	// 확인해야함 여기서 리콜이면 
	ChangeState(PlayerState::RECALL);
}

void Player_Zero::Movecalculation(float _DeltaTime)
{
	// ---------------------디버그용 -----------------------------
	if (true == m_DebugMode)
	{
		if (true == GameEngineInput::IsPress("LeftMove"))
		{
			SetMove(float4::Left * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Left * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("RightMove"))
		{
			SetMove(float4::Right * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Right * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("UpMove"))
		{
			SetMove(float4::Up * 3000.0f * _DeltaTime);
			GetLevel()->SetCameraMove(float4::Up * 3000.0f * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("DownMove"))
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
		// 중력 , 계속 아래로 떨어지는 힘이 더해진다 
		m_MoveDir += float4::Down * 200.0f * _DeltaTime;
	}

	// x축 이동값이 일정값을 넘어간다면 
	if (100.0f <= abs(m_MoveDir.x))
	{
		// x 축 값이 0보다 작다면 왼쪽이동,,.. 아 여기 영상으로 다시 봐  
		/*if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -100.0f;
		}
		else 
		{
			m_MoveDir.x = 100.0f;
		}*/
	}

	// 마찰력 
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x *= 0.001f;
	}

	// 임시로 배경으로 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColMap_Spaceport.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	// 충돌체크 
	bool Check = true;
	float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;

	if (RGB(255, 0, 255) == ColImage->GetPixelColor(NextPos, RGB(255, 0, 255)))
	{
		Check = false;
		m_MoveDir = float4::Zero;
	}

	
	// 잠깐주석 
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

	 SetMove(m_MoveDir *_DeltaTime);
	 // 일단 임시로 카메라무브 적용
	 GetLevel()->SetCameraMove(m_MoveDir * _DeltaTime);
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
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

	// 디버그용 위치출력시 참고할 코드 
	/*std::string MouseText = "MousePosition : ";
	MouseText += GetLevel()->GetMousePos().ToString();

	std::string CameraMouseText = "MousePositionCamera : ";
	CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();

	GameEngineLevel::DebugTextPush(MouseText);
	GameEngineLevel::DebugTextPush(CameraMouseText);*/
}
