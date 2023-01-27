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

// ����üũ
void Player_Zero::DirCheck(const std::string_view& _AnimationName)
{
	// ���� ���⹮�ڿ� ���� �޾ƿ´�. 
	std::string PrevDirString = m_DirString;
	// �ش��ϴ� ������ �ִϸ��̼����� change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());

	// ���� leftmove Ű�� ���ȴٸ�
	if (GameEngineInput::IsPress("LeftMove"))
	{
		// ���� ���⹮�ڿ��� left_ �� �����Ѵ�. 
		m_DirString = "Left_";
	}
	// ���� rightmove Ű�� ���ȴٸ� 
	else if (GameEngineInput::IsPress("RightMove"))
	{
		// ���� ���⹮�ڿ��� right_ �� �����Ѵ�.
		m_DirString = "Right_";
	}

	// ���� ���� 
	// ���� ���� ���⹮�ڿ��� ���� ���⹮�ڿ��� �ٸ��ٸ�
	if (PrevDirString != m_DirString)
	{
		m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	}
}

void Player_Zero::Start()
{
	// �÷��̾��� ��ġ

	// Ű����
	// ���ڿ��� Ű������ �Ͽ� ���ϴ� Ű�� 
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

	
	// ����������, ������ zorder �� �Է� 
	m_AnimationRender = CreateRender(RENDERORDER::PLAYER);
	m_AnimationRender->SetScale({ 640, 480 * 1.2f });
	// ����ü�� �־��ִµ� ���ϴ� ������ ���� �����Ͽ� �־��� �� �ִ�.
	// ��, ������ ���Ѽ� �־��־�� �������� ������ �ʴ´�. 

	// ���� 
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
	// ������ �⺻����
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack", .ImageName = "player_normal_attack_right.bmp" ,
									   .Start = 0, .End = 28, .InterTime = 0.035f , .Loop = false });


	// ���� ���̵�
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.15f });
	// ���� �������
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move_start",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	// ���� ����
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });
	// ���� �뽬 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash",  .ImageName = "player_doublejump_dash_sitattack_left.bmp",
									   .Start = 11, .End = 23 , .InterTime = 0.05f , .Loop = false });
	// ���� �⺻����
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack" , .ImageName = "player_normal_attack_left.bmp" ,
									   .Start = 0, .End = 28 , .InterTime = 0.035f , .Loop = false });

	// Ȯ���ؾ��� ���⼭ �����̸� 
	ChangeState(PlayerState::RECALL);
}

void Player_Zero::Movecalculation(float _DeltaTime)
{
	if (true == m_Gravity)
	{
		m_MoveDir += float4::Down * m_MoveSpeed * _DeltaTime;
	}

	// x�� �̵����� �������� �Ѿ�ٸ� 
	if (400.0f <= abs(m_MoveDir.x))
	{
		// x �� ���� 0���� �۴ٸ� �����̵�,,.. �� ���� �������� �ٽ� �� ���� 
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

	// �ӽ÷� ������� 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColMap_Spaceport.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}


	// �浹üũ 
	bool Check = true;
	float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;

	if (RGB(255, 0, 255) == ColImage->GetPixelColor(NextPos, RGB(255, 0, 255)))
	{
		Check = false;
		m_MoveDir = float4::Zero;
	}

	
	// ����ּ� 
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
	 // �ϴ� �ӽ÷� ī�޶󹫺� ����
	 GetLevel()->SetCameraMove(m_MoveDir * _DeltaTime);
}


// ������� �� ���� ������ ���� ����ؾ���. ������ ��. 
void Player_Zero::Update(float _DeltaTime)
{
	// ���� �÷��̾��� ���°��� ���� ������Ʈ�� ����.
	UpdateState(_DeltaTime);
	
	Movecalculation(_DeltaTime);
	
}

// ������Ʈ�� �߽����� �� �� �ֵ��� �簢�� ��� 
void Player_Zero::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

}
