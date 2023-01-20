#include "SigmaStageLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>

#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include "SigmaStage_BackGround.h"
#include "UI_PlayerHpBar.h"
#include "Map_SpacePort.h"

SigmaStageLevel::SigmaStageLevel()
{
}

SigmaStageLevel::~SigmaStageLevel()
{
}
 
void SigmaStageLevel::Loading()
{
	// �̹����ε�
	GameEngineDirectory Directory;
	
	// 1. ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SpacePortLevel");

	{
		// ������ ���̵� + �ȱ�
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_right.bmp"));
		Image->Cut( 8 , 3 );
	}
	{
		// ���� ���̵� + �ȱ�
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_left.bmp"));
		Image->Cut( 8, 3 );
	}
	{
		// ������ �뽬 + �������� ���� 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_doublejump_dash_sitattack_right.bmp"));
		Image->Cut(8, 5);
		float4 Scale = Image->GetImageScale();
	}
	{
		// ���� �뽬 + �������� ����
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_doublejump_dash_sitattack_left.bmp"));
		Image->Cut(8, 5);
	}
	{
		// ��׶���
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("sigmastage_background.bmp"));
	}
	{
		// �����̽���Ʈ ��
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort.bmp"));
	}
	
	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	Player = CreateActor<Player_Zero>();
	CreateActor<SigmaStage_BackGround>();
	//CreateActor<Map_SpacePort>();
	//CreateActor<SigmaStage_BackGround>();

	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		GameEngineInput::CreateKey("CameraLeftMove", 'A');
		GameEngineInput::CreateKey("CameraRightMove", 'D');
		GameEngineInput::CreateKey("CameraDownMove", 'S');
		GameEngineInput::CreateKey("CameraUpMove", 'W');
	}
}

void SigmaStageLevel::Update(float _DeltaTime)
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

void SigmaStageLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}
// �ھ� -> ��������
// ���� -> ���� �ȿ��� ����� ���� ����, ���� �� AcotrStart
// ���� -> ���Ͱ� �����ǰ� ���� �⺻������ �ʿ��� �κ� ����

// �ھ� : ������ ������ Update, Render ���� ��, ����ۿ� ������ۿ� ��µ� �̹����� �Ű��ش�. 
// ���� : ������ ������ Update, Render ������ ���
// ���� : 
