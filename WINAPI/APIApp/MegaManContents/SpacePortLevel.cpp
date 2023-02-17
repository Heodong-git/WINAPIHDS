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
#include "ContentsEnum.h"

SpacePortLevel::SpacePortLevel()
{
}

SpacePortLevel::~SpacePortLevel()
{
}
 
void SpacePortLevel::Loading()
{
	// �̹����ε�
	ImageLoad();
	// ����ε�
	SoundLoad();
	// ���ͷε�
	ActorLoad();
	// ī�޶�ε�
	CameraLoad();
}

void SpacePortLevel::Update(float _DeltaTime)
{
	float CameraMoveSpeed = 1000.0f;

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

	// q Ű�� ���ȴٸ� ����׸�� on , off 
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
	}
}

void SpacePortLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// �������
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Spaceport_bgm.wav");
	BGMPlayer.LoopCount(100);
	BGMPlayer.Volume(0.1f);

	m_Player->ChangeState(STATEVALUE::RECALL);
}

void SpacePortLevel::SoundLoad()
{
	// ���Ž�� 
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	Dir.Move("SpaceportLevel");

	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Spaceport_bgm.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_attack_first.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_attack_second.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_attack_third.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_saber_sound.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_dash_sound.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_recall_sound.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_jump_sound.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_wall_jump_sound.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_landing_sound.wav"));	
}



void SpacePortLevel::ImageLoad()
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
		// ���� ������ ��������Ʈ 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_zero_sprite_right.bmp"));
		Image->Cut(12, 16);
	}
	{
		// ���� ���� ��������Ʈ
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_zero_sprite_left.bmp"));
		Image->Cut(12, 16);
	}
	{
		// UI HpBar
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ui_hp_bar.bmp"));
		Image->Cut(8, 5);
	}

	{
		// �����̽���Ʈ ��
		// GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ColMap_SpacePort.bmp"));
	}
	{
		// �����̽���Ʈ ���Ҹ� 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_0.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_1.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_2.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_3.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_4.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_5.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_6.bmp"));
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

	// ����Ʈ
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("effect_dash_right.bmp"));
		Image->Cut(5, 2);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("effect_dash_left.bmp"));
		Image->Cut(5, 2);
	}
}
void SpacePortLevel::ActorLoad()
{
	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	m_Player = CreateActor<Player_Zero>(ZORDER::PLAYER);
	m_Player->SetPos({ 400, 7160 });
	m_Player->SetStartPos(m_Player->GetPos());
	// �ϴ� �÷��̾� �ִϸ��̼Ǻ��� �ʿ��Ѱ� �� �����ϰ��� �ٽ�. 
	GameEngineActor* Boss = CreateActor<Boss_Colonel>(ZORDER::BOSS);
	Boss->SetPos({ 18587, 968 });

	/*GameEngineActor* PlayerHpBar = CreateActor<UI_PlayerHpBar>(ZORDER::UI);
	PlayerHpBar->SetPos(m_Player->GetPos() + float4 { - 200 , - 350});*/

	CreateActor<Map_SpacePort>();
	Monster_GunMan* Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 1738 , 7065 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	/*Monster->SetPos({ 2334, 6382 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 2354 , 6382 });*/
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 3186 , 7058 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 5366, 6825 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 5379, 6385 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 12827, 6384 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 15259, 3932 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 15521, 5371 });
}
void SpacePortLevel::CameraLoad()
{
	// ī�޶� Ű����
	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		GameEngineInput::CreateKey("CameraLeftMove", 'A');
		GameEngineInput::CreateKey("CameraRightMove", 'D');
		GameEngineInput::CreateKey("CameraDownMove", 'S');
		GameEngineInput::CreateKey("CameraUpMove", 'W');
	}

	// ����׷��� ����ġ ����
	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", '2');
	}

	// ���⼭ ī�޶� ��ġ ������ �ƾ�
	m_StartCameraPos = GameEngineWindow::GetScreenSize().half() + float4{ -580 , 5760 };
	SetCameraMove(m_StartCameraPos);
}
// �ھ� -> ��������
// ���� -> ���� �ȿ��� ����� ���� ����, ���� �� AcotrStart
// ���� -> ���Ͱ� �����ǰ� ���� �⺻������ �ʿ��� �κ� ����

// �ھ� : ������ ������ Update, Render ���� ��, ����ۿ� ������ۿ� ��µ� �̹����� �Ű��ش�. 
// ���� : ������ ������ Update, Render ������ ���
// ���� : 
