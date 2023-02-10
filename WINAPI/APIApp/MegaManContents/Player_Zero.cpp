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

// ����׿� ���� 
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
	// ���� ���⹮�ڿ� ���� �޾ƿ´�. 
	std::string PrevDirString = m_DirString;
	// �ش��ϴ� ������ �ִϸ��̼����� change
	m_AnimationRender->ChangeAnimation(m_DirString + _AnimationName.data());
	
	// ���� leftmove Ű�� ���ȴٸ�
	if (GameEngineInput::IsPress("Left_Move"))
	{
		// ���� ���⹮�ڿ��� left_ �� �����Ѵ�. 
		m_DirString = "Left_";
	}
	// ���� rightmove Ű�� ���ȴٸ� 
	else if (GameEngineInput::IsPress("Right_Move"))
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

// ���� �̵���ġ üũ
bool Player_Zero::NextMoveCheck(float _DeltaTime)
{
	float4 NextPos = GetPos() + m_MoveDir * _DeltaTime;
	if (NextPos.x < m_StartPos.x)
	{
		m_MoveDir = float4::Zero;
		return false;
	}

	return true;
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

	// ����������, ������ zorder �� �Է� 
	m_AnimationRender = CreateRender(ZORDER::PLAYER);
	m_AnimationRender->SetScale({ 1280 , 960 });

	// �ִϸ��̼� ����
	PlayerCreateAnimation();

	// �÷��̾� �ö��̴�
	m_Collider = CreateCollision(COLORDER::PLAYER);
	m_Collider->SetScale({ 150, 150 });
	m_Collider->SetDebugRenderType(CT_Rect);
	m_Collider->SetPosition(float4{ 0, -80 });

	// ���⼭���� �ٽ�
	// ������ �ö��̴�
	m_SaberCollider = CreateCollision(COLORDER::PLAYERATTACK);
	
	ChangeState(STATEVALUE::RECALL);
}


// ������� �� ���� ������ ���� ����ؾ���. ������ ��. 
void Player_Zero::Update(float _DeltaTime)
{
	// ����� Ű�� �������� üũ�� ������ ���־�� �ϴϱ� ����ٰ�.
	if (true == GameEngineInput::IsDown("DebugMode"))
	{
		DebugSwitch();
		return;
	}
	// --------------------- ����׿� �̵� -----------------------------
	// ����� �̵��� ��� �̵��ϰ� �ƹ��͵� �������� �ʾƾ���. 
	if (true == m_DebugMode)
	{
		DebugMove(_DeltaTime);
		return;
	}

	// ���� �÷��̾��� ���°��� ���� ������Ʈ�� ����.
	UpdateState(_DeltaTime);
}


bool Player_Zero::IsGround(float4 Pos)
{
	// �� ��ġ�� �ȼ����� �������� �ƴ϶�� 
	// ���� ground ���°� �ƴ� ���̴�. 

	// IsGround �� true �� ����
	// ���� ���� �� �ȼ��� ���� ������ �� �ȼ���ġ�� ���� ������ �Ʒ��ȼ� ��ġ�� ���� ����̶�� ���̾�
	// IsGround �� false �� ����
	// ���� �Ʒ��ȼ��� ����̸� ���� �ƴϾ�
	// �ϴ� �̰Ŵ� ���� ���� , ����������Ʈ ���������� �ٽ� ��
	// �ָ����� �浹�̹����� �����Ϸ��ؾ���
	return RGB(0, 0, 0) != GetColor(Pos);
}

int Player_Zero::GetColor(float4 Pos)
{
	// �� ��ġ�� �ȼ����� �������� �� + ��ġ�� �ȼ����� �޾ƿ´�. 
	float4 CheckPos = GetPos() + Pos;

	// ����� �Ⱦ��°� ����. <-- �����ϰ�
	// �浹���� ���ٸ� assert 
	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(ColMapName);
	if (nullptr == ColImage)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
		return RGB(0,0,0);
	}

	// �÷�üũ ���Ͽ��� Ȱ���Ͽ� ������ �´��� üũ�Ѵ�. 
	ColorCheck CC;

	// �浹���̹������� �ش��ϴ� ��ġ�� �ȼ����� �޾Ƽ� �����Ѵ�. 
	CC.Color = ColImage->GetPixelColor(CheckPos, RGB(255, 255, 255));
	return CC.Color;
}

// �߷������ ȣ���� �Լ� 
void Player_Zero::Gravity(float _DeltaTime)
{
	m_MoveDir += float4::Down * 250.0f * _DeltaTime;
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
}


void Player_Zero::GroundCollisionCheck(float4 _Pos)
{
	while (IsGround(_Pos))
	{
		SetMove(float4::Up);
	}	
}



//m_Collision->DebugRender();	
	// ����׿� ��ġ��½� ������ �ڵ� 
	/*std::string MouseText = "MousePosition : ";
	MouseText += GetLevel()->GetMousePos().ToString();

	std::string CameraMouseText = "MousePositionCamera : ";
	CameraMouseText += GetLevel()->GetMousePosToCamera().ToString();

	GameEngineLevel::DebugTextPush(MouseText);
	GameEngineLevel::DebugTextPush(CameraMouseText);*/

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



void Player_Zero::PlayerCreateAnimation()
{
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
									   .Start = 19 , .End = 22 , .InterTime = 0.1f , .Loop = false });

	// ������ fall 
	m_AnimationRender->CreateAnimation({ .AnimationName = "right_fall" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 23 , .End = 30 , .InterTime = 0.03f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "right_fall_end" , .ImageName = "player_zero_sprite_right.bmp",
									   .Start = 30 , .End = 30 , .InterTime = 0.001f , .Loop = false });


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
									   .Start = 127 , .End = 129 , .InterTime = 0.07f , .Loop = false });

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
									   .Start = 19 , .End = 25 , .InterTime = 0.1f });

	// ���� ����
	m_AnimationRender->CreateAnimation({ .AnimationName = "left_fall" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 26 , .End = 30 , .InterTime = 0.03f , .Loop = false });

	m_AnimationRender->CreateAnimation({ .AnimationName = "left_fall_end" , .ImageName = "player_zero_sprite_left.bmp",
									   .Start = 30 , .End = 30 , .InterTime = 0.001f , .Loop = false });


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
}
