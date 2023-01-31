#include "SpacePortLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player_Zero.h"
#include "Monster_Gunman.h"
#include "Monster_NightMareVirus.h"
#include "UI_PlayerHpBar.h"
#include "Map_SpacePort.h"
#include "Boss_Colonel.h"

SpacePortLevel::SpacePortLevel()
{
}

SpacePortLevel::~SpacePortLevel()
{
}
 
void SpacePortLevel::Loading()
{
	// �̹����ε�
	GameEngineDirectory Directory;

	// 1. ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SpacePortLevel");

	// �÷��̾�
	{
		// ���� 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
		Image->Cut(8, 3);
	}
	{
		// ������ ���̵� + �ȱ�
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_right.bmp"));
		Image->Cut(8, 3);
	}
	{
		// ���� ���̵� + �ȱ�
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_left.bmp"));
		Image->Cut(8, 3);
	}
	{
		// ������ �뽬 + �������� ���� 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_doublejump_dash_sitattack_right.bmp"));
		Image->Cut(8, 5);
	}
	{
		// ���� �뽬 + �������� ����
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_doublejump_dash_sitattack_left.bmp"));
		Image->Cut(8, 5);
	}
	{
		// ���� �⺻����
		// attack right 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_normal_attack_right.bmp"));
		Image->Cut(8, 4);
	}
	{
		// ���� �⺻���� 
		// attack left
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_normal_attack_left.bmp"));
		Image->Cut(8, 4);
	}
	{
		// ����, ��������
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_jump_jumpattack_right.bmp"));
		Image->Cut(8, 4);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_jump_jumpattack_left.bmp"));
		Image->Cut(8, 4);
	}
	{
		// ��������, ��Ʈ�� �����ϴ°� �̸��� �����̾ȳ��� 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_rope_attacked_right.bmp"));
		Image->Cut(8, 3);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_rope_attacked_left.bmp"));
		Image->Cut(8, 3);
	}

	{
		// �����̽���Ʈ ��
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ColMap_SpacePort.bmp"));
	}

	// ���� Ŀ��
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_colonel_left.bmp"));
		Image->Cut(8, 6);
	}

	// ����

	// gunman image
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_left.bmp"));
		Image->Cut(8, 5);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_right.bmp"));
		Image->Cut(8, 5);
	}

	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	Player = CreateActor<Player_Zero>();
	Player->SetPos({ 400, 7000 });
	// �ϴ� �÷��̾� �ִϸ��̼Ǻ��� �ʿ��Ѱ� �� �����ϰ��� �ٽ�. 
	/*GameEngineActor* Boss = CreateActor<Boss_Colonel>();
	Boss->SetPos({ 600, 7050 });*/
	CreateActor<Map_SpacePort>();
	GameEngineActor* Monster = CreateActor<Monster_GunMan>();
	Monster->SetPos({ 1738 , 7065 });
	// �Ǹ� 01 SetPos ��
	// 1738, 7065
	// 2334, 6382
	// 2354, 6382 
	// 3186, 7058 
	// 5366, 6825 
	// 5379, 6385
	// 5910, 6609 
	// 12827, 6384
	// 15521, 5371 
	
	// �Ǹ� 02 SetPos �� 
	// 2575 , 6904


	// ī�޶� Ű����
	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		GameEngineInput::CreateKey("CameraLeftMove", 'A');
		GameEngineInput::CreateKey("CameraRightMove", 'D');
		GameEngineInput::CreateKey("CameraDownMove", 'S');
		GameEngineInput::CreateKey("CameraUpMove", 'W');
	}

	SetCameraMove(GameEngineWindow::GetScreenSize().half() + float4{ -580 , 5690 });
}

void SpacePortLevel::Update(float _DeltaTime)
{
	float CameraMoveSpeed = 2000.0f;

	if (GameEngineInput::IsPress("CameraLeftMove"))
	{
		SetCameraMove(float4::Left * _DeltaTime * CameraMoveSpeed);
	}
	if (GameEngineInput::IsPress("CameraRightMove"))
	{
		SetCameraMove(float4::Right * _DeltaTime * CameraMoveSpeed);
	}
	if (GameEngineInput::IsPress("CameraDownMove"))
	{
		SetCameraMove(float4::Down * _DeltaTime * CameraMoveSpeed);
	}
	if (GameEngineInput::IsPress("CameraUpMove"))
	{
		SetCameraMove(float4::Up * _DeltaTime * CameraMoveSpeed);
	}
}

void SpacePortLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}
// �ھ� -> ��������
// ���� -> ���� �ȿ��� ����� ���� ����, ���� �� AcotrStart
// ���� -> ���Ͱ� �����ǰ� ���� �⺻������ �ʿ��� �κ� ����

// �ھ� : ������ ������ Update, Render ���� ��, ����ۿ� ������ۿ� ��µ� �̹����� �Ű��ش�. 
// ���� : ������ ������ Update, Render ������ ���
// ���� : 
