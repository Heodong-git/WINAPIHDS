#include "Player_Zero.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

float Player_Zero::Time = 0.0f;

Player_Zero::Player_Zero() :
	AnimationRender(nullptr)
{
}

Player_Zero::~Player_Zero()
{
}

// ����üũ
void Player_Zero::DirCheck(const std::string_view& _AnimationName)
{
	// ���� ���⹮�ڿ� ���� �޾ƿ´�. 
	std::string PrevDirString = DirString;
	// �ش��ϴ� ������ �ִϸ��̼����� change
	AnimationRender->ChangeAnimation(DirString + _AnimationName.data());

	// ���� leftmove Ű�� ���ȴٸ�
	if (GameEngineInput::IsPress("LeftMove"))
	{
		// ���� ���⹮�ڿ��� left_ �� �����Ѵ�. 
		DirString = "Left_";
	}
	// ���� rightmove Ű�� ���ȴٸ� 
	else if (GameEngineInput::IsPress("RightMove"))
	{
		// ���� ���⹮�ڿ��� right_ �� �����Ѵ�.
		DirString = "Right_";
	}

	// ���� ���� 
	// ���� ���� ���⹮�ڿ��� ���� ���⹮�ڿ��� �ٸ��ٸ�
	if (PrevDirString != DirString)
	{
		AnimationRender->ChangeAnimation(DirString + _AnimationName.data());
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

	// �÷��̾� ũ�� 165 , 200 
	SetPos({GameEngineWindow::GetScreenSize().half().x , 
		   (GameEngineWindow::GetScreenSize().half().y) + (GameEngineWindow::GetScreenSize().half().y / 2)});
	
	// ����������, ������ zorder �� �Է� 
	AnimationRender = CreateRender(RENDERORDER::PLAYER);
	AnimationRender->SetScale({ 400, 400 });

	// ����ü�� �־��ִµ� ���ϴ� ������ ���� �����Ͽ� �־��� �� �ִ�.
	// ��, ������ ���Ѽ� �־��־�� �������� ������ �ʴ´�. 

	// ���� 
	AnimationRender->CreateAnimation({ .AnimationName = "right_idle",  .ImageName = "player_idle_walk_right.bmp", 
									   .Start = 0, .End = 5 , .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "right_move_start",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	AnimationRender->CreateAnimation({ .AnimationName = "right_move",  .ImageName = "player_idle_walk_right.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });

	// ����
	AnimationRender->CreateAnimation({ .AnimationName = "left_idle",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 0, .End = 5 , .InterTime = 0.2f });
	AnimationRender->CreateAnimation({ .AnimationName = "left_move_start",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 6, .End = 7 , .InterTime = 0.5f });
	AnimationRender->CreateAnimation({ .AnimationName = "left_move",  .ImageName = "player_idle_walk_left.bmp",
									   .Start = 8, .End = 21 , .InterTime = 0.05f });


	ChangeState(PlayerState::IDLE);
}

void Player_Zero::Update(float _DeltaTime)
{
	// ���� �÷��̾��� ���°��� ���� ������Ʈ�� ����.
	UpdateState(_DeltaTime);
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
