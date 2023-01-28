#include "Player_Zero.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

float Player_Zero::m_Time = 0.0f;

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

// 방향체크
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
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
	}

	
	// 렌더러생성, 생성시 zorder 값 입력 
	m_AnimationRender = CreateRender(RENDERORDER::PLAYER);
	m_AnimationRender->SetScale({ 640 * 1.1f , 480 * 1.6f });
	// 구조체를 넣어주는데 원하는 변수의 값만 수정하여 넣어줄 수 있다.
	// 단, 순서는 지켜서 넣어주어야 빨간줄이 그이지 않는다. 

	// 우측 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_recall" , .ImageName = "player_recall.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.07f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle",  .ImageName = "player_idle_walk_right.bmp", 
									   .Start = 0, .End = 5 , .InterTime = 0.15f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move_start",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_dash",  .ImageName = "player_doublejump_dash_sitattack_right.bmp",
									   .Start = 11, .End = 23 , .InterTime = 0.05f , .Loop = false  });
	// 오른쪽 기본공격
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack", .ImageName = "player_normal_attack_right.bmp" ,
									   .Start = 0, .End = 28, .InterTime = 0.035f , .Loop = false });


	// 왼쪽 아이들
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.15f });
	// 왼쪽 무브시작
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move_start",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	// 왼쪽 무브
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });
	// 왼쪽 대쉬 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash",  .ImageName = "player_doublejump_dash_sitattack_left.bmp",
									   .Start = 11, .End = 23 , .InterTime = 0.05f , .Loop = false });
	// 왼쪽 기본공격
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack" , .ImageName = "player_normal_attack_left.bmp" ,
									   .Start = 0, .End = 28 , .InterTime = 0.035f , .Loop = false });

	// 확인해야함 여기서 리콜이면 
	ChangeState(PlayerState::RECALL);
}

void Player_Zero::Movecalculation(float _DeltaTime)
{
	if (true == m_Gravity)
	{
		m_MoveDir += float4::Down * m_MoveSpeed * _DeltaTime;
	}

	// x축 이동값이 일정값을 넘어간다면 
	if (400.0f <= abs(m_MoveDir.x))
	{
		// x 축 값이 0보다 작다면 왼쪽이동,,.. 아 여기 영상으로 다시 봐 ㅅㅂ 
		if (0 > m_MoveDir.x)
		{
			m_MoveDir.x = -400.0f;
		}
		else 
		{
			m_MoveDir.x = 400.0f;
		}
	}

	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x *= 0.01f;
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
	// 현재 플레이어의 상태값에 따라 업데이트를 진행.
	UpdateState(_DeltaTime);
	
	Movecalculation(_DeltaTime);
	
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

}
