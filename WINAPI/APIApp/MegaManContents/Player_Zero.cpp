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

float Player_Zero::m_Time = 0.0f;

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

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
		GameEngineInput::CreateKey("Sit", VK_DOWN);
		GameEngineInput::CreateKey("DownMove", VK_DOWN);
		GameEngineInput::CreateKey("Dash", 'Z');
		GameEngineInput::CreateKey("Attack", 'X');
		GameEngineInput::CreateKey("Jump", 'C');
		GameEngineInput::CreateKey("DebugMode", 'Q');
	}

	// ����������, ������ zorder �� �Է� 
	m_AnimationRender = CreateRender(ZORDER::PLAYER);
	m_AnimationRender->SetScale({ 1280 , 960 });

	m_Collision = CreateCollision(COLORDER::PLAYER);
	m_Collision->SetScale({ 100, 100 });
	
	// ����
	// 0 ~ 18
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_recall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.075f });
	// ������ ���̵�
	// 14 ~ 18
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 14 , .End = 18 , .InterTime = 0.14f });

	// �ٵ� ������ ������ �������� �� ���� �ö󰡴µ� �ִϸ��̼� �ٸ���� ����.
	// ������ ����
	// 19 ~ 31 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 19 , .End = 31 , .InterTime = 0.08f , .Loop = false });

	// 31~32 ��������ε� �ϴ�. ��..�ϴ� ������ 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_landing" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 30 , .End = 32 , .InterTime = 0.4f });


	// ������ ����
	// 37 ~ 50
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_move" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 37 , .End = 50 , .InterTime = 0.04f });
	// ������ ����
	// 51~91 ���� 1~3Ÿ
	// 1Ÿ : 51 ~ 66 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_first" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 51 , .End = 66 , .InterTime = 0.025f });
	// 2Ÿ 67 ~ 78
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_second" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 67 , .End = 78 , .InterTime = 0.025f });

	// 3Ÿ 79 ~ 92
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_normal_attack_third" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 79 , .End = 92 , .InterTime = 0.025f });

	// ������ �������� 93 ~ 101
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_jump_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 93 , .End = 101 , .InterTime = 0.03f });

	// ������ �뽬 111 ~ 121 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_dash" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 111 , .End = 121 , .InterTime = 0.05f });

	// ������ ��Ÿ�� ���
	// 122~126
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 122 , .End = 126 , .InterTime = 0.5f , .Loop = false });

	// ������ ��Ÿ�� �� ����
	// 127 ~ 129 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall_jump" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 127 , .End = 129 , .InterTime = 0.07f , .Loop = false});
	
	// ������ ��Ÿ�� �� ���� 
	// 130 ~ 138 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_wall_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 130 , .End = 138 , .InterTime = 0.05f , .Loop = false });

	// ����� �� 
	// ��ٸ� Ÿ��
	// 139 ~ 148 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 139 , .End = 148 , .InterTime = 0.06f });
	
	// ��ٸ� ��������  �ö󰡴� ���
	// 149 ~ 152 
	// ���߿� �ٽ� �պ��� �� ����. �ȼ� ��¦ �ָ���
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup_end" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 149 , .End = 152 , .InterTime = 0.07f });

	// ��ٸ� Ÿ���� ���� 
	// 153 ~ 161
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_rideup_attack" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 153 , .End = 161 , .InterTime = 0.05f });

	// ������ �ǰ�
	// 162 ~ 165
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_hit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 162 , .End = 165 , .InterTime = 0.14f });

	// ����ü�� ���� ���̵�
	// 166 ~ 169
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_idle_tiring" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 166 , .End = 169 , .InterTime = 1.0f });

	// ��� �ǰ�
	// 170 ~ 176
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_big_hit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 170 , .End = 176 , .InterTime = 0.15f });

	// exit 
	// 177 ~ 189
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_exit" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 177 , .End = 189 , .InterTime = 0.09f });

	// ---------------------------------- ���� ---------------------------------------------



	// ���� ����
	// 0 ~ 18 ,  0.075
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_recall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 0 , .End = 18 , .InterTime = 0.075f });
	// ���� ���̵�
	// 14 ~ 18 , 0.14
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 14 , .End = 18 , .InterTime = 0.14f });

	// �ٵ� ������ ������ �������� �� ���� �ö󰡴µ� �ִϸ��̼� �ٸ���� ����.
	// ���� ����
	// 19 ~ 31 , 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 19 , .End = 31 , .InterTime = 0.15f });

	// 31~32 ��������ε� �ϴ�. ��..�ϴ� ������ 
	// 30 ~ 32 ? 0.4
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_landing" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 30 , .End = 32 , .InterTime = 0.4f });


	// ���� ����
	// 37 ~ 50
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_move" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 37 , .End = 50 , .InterTime = 0.04f });
	// ���� ����
	// 51~91 ���� 1~3Ÿ
	// 1Ÿ : 51 ~ 66 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_first" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 51 , .End = 66, .InterTime = 0.025f });
	// 2Ÿ 67 ~ 78 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_second" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 67 , .End = 78 , .InterTime = 0.025f });

	// 3Ÿ 79 ~ 92 0.025
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_normal_attack_third" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 79 , .End = 92 , .InterTime = 0.025f });

	// ���� �������� 93 ~ 101
	// ����ѰŰ�����
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_jump_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 93 , .End = 101 , .InterTime = 0.03f });

	// ���� �뽬 111 ~ 121 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_dash" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 111 , .End = 121 , .InterTime = 0.05f });

	// ������ ��Ÿ�� ���
	// 122~126
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 122 , .End = 126 , .InterTime = 0.5f , .Loop = false });

	// ������ ��Ÿ�� �� ����
	// 127 ~ 129 0.07
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall_jump" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 126 , .End = 129 , .InterTime = 0.07f , .Loop = false });

	// ������ ��Ÿ�� �� ���� 
	// 130 ~ 138 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_wall_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 130 , .End = 138 , .InterTime = 0.04f , .Loop = false });

	// ����� �� 
	// ��ٸ� Ÿ��
	// 139 ~ 148 0.06
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 139 , .End = 148 , .InterTime = 0.06f });

	// ��ٸ� ��������  �ö󰡴� ���
	// 149 ~ 152 
	// ���߿� �ٽ� �պ��� �� ����. �ȼ� ��¦ �ָ���
	// �̰� ���߿� �ٽ� 
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup_end" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 149 , .End = 152 , .InterTime = 0.07f });

	// ��ٸ� Ÿ���� ���� 
	// 153 ~ 161 0.05
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_rideup_attack" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 153 , .End = 161 , .InterTime = 0.05f });

	// ���� �ǰ�
	// 162 ~ 165 0.14
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_hit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 162 , .End = 165 , .InterTime = 0.014f });

	// ����ü�� ���� ���̵�
	// 166 ~ 169 1.0
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_idle_tiring" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 166 , .End = 169 , .InterTime = 1.0f });

	// ��� �ǰ�
	// 170 ~ 176 0.15
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_big_hit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 170 , .End = 175 , .InterTime = 0.15f });

	// exit 
	// 177 ~ 189 0.09
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_exit" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 177 , .End = 189 , .InterTime = 0.09f });

	// Ȯ���ؾ��� ���⼭ �����̸� 
	ChangeState(PlayerState::RECALL);
}

void Player_Zero::Movecalculation(float _DeltaTime)
{
	// ---------------------����׿� -----------------------------
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
		
		// ����׿�
		// ������ġ üũ
		float4 CurPos = GetPos();
		return;
	}

	// ---------------------����  ���� �÷��̿� ---------------------------- 

	if (true == m_Gravity)
	{
		// �߷� , ��� �Ʒ��� �������� ���� �������� 
		if (true == m_Jump)
		{
			m_MoveDir += float4::Down * (m_GravityPower * 2.5f) * _DeltaTime;
		}

		else
		{
			m_MoveDir += float4::Down * m_GravityPower * _DeltaTime;
		}
	}


	// �÷��̾� �ӷ� ����
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

	// ������ 
	// ��� ����
	if (false == GameEngineInput::IsPress("LeftMove") && false == GameEngineInput::IsPress("RightMove"))
	{
		m_MoveDir.x *= 0.001f;
	}

	// �ӽ÷� ������� 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind("ColMap_Spaceport.BMP");
	if (nullptr == ColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}


	// �浹üũ ����  
	bool Check = true;
	// ���� �̵���ġ ���
	float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;

	// ���� �̵���ġ�� �ȼ� ���� 255, 0 , 255 ��� �浹�� ���̴�. 
	if (RGB(255, 0, 255) == ColImage->GetPixelColor(NextPos, RGB(255, 0, 255)))
	{
		Check = false;
		m_Ground = true;

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


	// ī�޶�� X���� �������ų� Y���� ���ҵǴ°� �ƴ϶�� �������� �ʴ´�.
	SpacePortLevel* PlayLevel = dynamic_cast<SpacePortLevel*>(GetLevel());

	if (nullptr == PlayLevel)
	{
		MsgAssert("�޾ƿ� ������ SpacePort ������ �ƴմϴ�.");
		return;
	}

	// �÷��̾��� ���� ��ġ�� ���� ��ġ.
	float4 PrevPos = GetPos();
	// ���� ��ġ�� ������ġ + �̵����� * DeltaTime; 
	float4 PlayerNextPos = PrevPos + m_MoveDir * _DeltaTime;
	// �÷��̾�� ó���� ������ ��ġ���� �ڷδ� ����
	if (PlayLevel->GetStatingPos().x > PlayerNextPos.x)
	{
		// �ٽ� ������ġ��
		SetPos(PrevPos);
		return;
	}

	// ī�޶� ������ġ �޾ƿ���. 
	float4 limitCameraPos = PlayLevel->GetStartCameraPos();
	// ���� ī�޶� ��ġ�� �޾ƿ���. 
	float4 CurCameraPos = GetLevel()->GetCameraPos();

	// �÷��̾ �����̰�.
	SetMove(m_MoveDir * _DeltaTime);

	// ����ī�޶���ġ �޾ƿ���
	float4 PrevCameraPos = GetLevel()->GetCameraPos();
	// ������ġ�� ������ġ + �̵����� 
	float4 NextCameraPos = PrevCameraPos + m_MoveDir * _DeltaTime;

	// ī�޶� ������. 
	// ī�޶� �÷��̾ ó������ ������ ����
	// �÷��̾��� ��ġ�� ������x ���� ������ Ŀ�������� ����
	if (GameEngineWindow::GetScreenSize().half().x <= GetPos().x)
	{
		GetLevel()->SetCameraMove(m_MoveDir *_DeltaTime);
	}

	if (NextCameraPos.x < limitCameraPos.x || NextCameraPos.y > limitCameraPos.y )
	{
		// ���ѵ� ��ġ�� ����
		GetLevel()->SetCameraPos(PrevCameraPos);
		return;
	}
}



// ������� �� ���� ������ ���� ����ؾ���. ������ ��. 
void Player_Zero::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("DebugMode"))
	{
		DebugSwitch();
	}
	// ���� �÷��̾��� ���°��� ���� ������Ʈ�� ����.
	UpdateState(_DeltaTime);
	
	Movecalculation(_DeltaTime);

	// �ø������� ���ÿ��ڵ� 
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

// ������Ʈ�� �߽����� �� �� �ֵ��� �簢�� ��� 
void Player_Zero::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() -GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);

	// ����׿� ��ġ��½� ������ �ڵ� 
	/*std::string MouseText = "MousePosition : ";
	MouseText += GetLevel()->GetMousePos().ToString();

	std::string CameraMouseText = "MousePositionCamera : ";
	CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();

	GameEngineLevel::DebugTextPush(MouseText);
	GameEngineLevel::DebugTextPush(CameraMouseText);*/
}
