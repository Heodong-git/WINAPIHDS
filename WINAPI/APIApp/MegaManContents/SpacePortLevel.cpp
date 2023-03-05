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
#include "Ladder.h"
#include "Object_Door.h"
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

	// ī�޶� ������ġ�� �����ߴٸ� ����Ŭ��� true �� �����Ͽ� �Ʒ� �ڵ尡 �������� �ʵ��� ó���Ѵ�. 
	if (true == m_SectionClear)
	{
		return; 
	}
	// ���⼭�� �÷��̾��� ��ġ�� üũ�Ѵ�.
	// �÷��̾ �ش� ���� ��ġ�� �Ѿ�ٸ� ���� �ö󰡴� ������ ������ ���̱� ������ true �� ����
	if (GetCameraPos().x > 14800.0f)
	{
		m_HeightSection = true;
		m_FirstSection = true;
	}

	// ù��° ���ǿ� �������� �� 
	// �÷��̾��� y�� ��ġ�� ���� ī�޶��� y�� ��ġ�� �Ѿ�ٸ�
	// ī�޶��� y�� ���� - ���Ѽ� ���������� ī�޶� ��ġ���� �̵���Ų��. 
	
	// ���⼭ �÷��̾ ���������Ǳ��������������� ��ǥ�� �����ͼ� 

	if (true == m_FirstSection)
	{
		if (m_Player->GetPos().y <= 6600.0f)
		{
			float4 EndPosY = m_FirstSectionPos - float4{ 0, GameEngineWindow::GetScreenSize().y };

			SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);

			if (GetCameraPos().y <= EndPosY.y)
			{
				SetCameraPos(m_SecondSectionPos);
				m_FirstSection = false;
			}
		}
	}

	// --------------------

	bool PosCheck = 5000.0f < m_Player->GetPos().y;
	bool PosCheck2 = 5680.0f >= m_Player->GetPos().y;
	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_SecondSection = true;
	}

	if (true == m_SecondSection)
	{
		float4 EndPosY = m_SecondSectionPos - float4{ 0 , GameEngineWindow::GetScreenSize().half().y};
		SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);
		
		if (GetCameraPos().y <= EndPosY.y)
		{
			SetCameraPos(m_ThirdSectionPos);
			m_SecondSection = false;
		}
	}

	// ---------------------- 

	PosCheck = 4000.0f < m_Player->GetPos().y;
	PosCheck2 = 5000.0f >= m_Player->GetPos().y;
	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_ThirdSection = true;
	}

	if (true == m_ThirdSection)
	{
		float4 EndPosY = m_ThirdSectionPos - float4{ 0 , GameEngineWindow::GetScreenSize().y};
		SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);

		if (GetCameraPos().y <= EndPosY.y)
		{
			SetCameraPos(m_FourthSectionPos);
			m_ThirdSection = false;
		}
	}	

	// ------------------

	PosCheck = 4000.0f > m_Player->GetPos().y;
	PosCheck2 = 3400.0f <= m_Player->GetPos().y;
	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_FourthSection = true;
	}

	if (true == m_FourthSection)
	{
		float4 EndPosY = m_FourthSectionPos - float4{ 0 , GameEngineWindow::GetScreenSize().half().y};
		SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);

		if (GetCameraPos().y <= EndPosY.y)
		{
			SetCameraPos(m_FifthSectionPos);
			m_FourthSection = false;
		}
	}

	PosCheck = 3400.0f > m_Player->GetPos().y;
	PosCheck2 = 2640.0f <= m_Player->GetPos().y;
	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_FifthSection = true;
	}

	if (true == m_FifthSection)
	{
		float4 EndPosY = m_FifthSectionPos - float4{ 0 , GameEngineWindow::GetScreenSize().y };
		SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);

		if (GetCameraPos().y <= EndPosY.y)
		{
			SetCameraPos(m_SixthSectionPos);
			m_FifthSection = false;
		}
	}

	// --------------------------------------

	PosCheck = 2640.0f > m_Player->GetPos().y;
	PosCheck2 = 1750.0f <= m_Player->GetPos().y;

	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_SixthSection = true;
	}

	if (true == m_SixthSection)
	{
		SetCameraMove(float4::Up * m_CameraMoveSpeed * _DeltaTime);

		if (GetCameraPos().y <= m_SeventhSectionPos.y)
		{
			SetCameraPos(m_SeventhSectionPos);
			m_SixthSection = false;
		}
	}

	// -----------------------------------------

	PosCheck = 1750.0f > m_Player->GetPos().y;
	PosCheck2 = 1230.0f <= m_Player->GetPos().y;
	
	if (true == m_HeightSection && true == PosCheck && true == PosCheck2)
	{
		m_SeventhSection = true;
	}

	if (true == m_SeventhSection)
	{
		SetCameraMove(float4::Up* m_CameraMoveSpeed* _DeltaTime);

		if (GetCameraPos().y <= m_EighthSectionPos.y)
		{
			SetCameraPos(m_EighthSectionPos);
			m_SeventhSection = false;
		}
	}

	// ------------------------

	PosCheck = 1230.0f > m_Player->GetPos().y;
	if (true == m_HeightSection && true == PosCheck)
	{
		m_EightSection = true;
	}

	if (true == m_EightSection)
	{
		SetCameraMove(float4::Up* m_CameraMoveSpeed* _DeltaTime);

		if (GetCameraPos().y <= m_NinthSectionPos.y)
		{
			SetCameraPos(m_NinthSectionPos);
			m_EightSection = false;
			m_HeightSection = false;
			m_SectionClear = true;
		}
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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("player_wall_effect_sound.wav"));
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

	// ��
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("object_boss_door.bmp"));
		Image->Cut(4, 4);
	}
}
void SpacePortLevel::ActorLoad()
{
	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	m_Player = CreateActor<Player_Zero>(ZORDER::PLAYER);
	m_Player->SetPos({ 400, 7060 });
	m_Player->SetStartPos(m_Player->GetPos());
	// �ϴ� �÷��̾� �ִϸ��̼Ǻ��� �ʿ��Ѱ� �� �����ϰ��� �ٽ�. 
	GameEngineActor* Boss = CreateActor<Boss_Colonel>(ZORDER::BOSS);
	Boss->SetPos({ 18587, 978 });

	/*GameEngineActor* PlayerHpBar = CreateActor<UI_PlayerHpBar>(ZORDER::UI);
	PlayerHpBar->SetPos(m_Player->GetPos() + float4 { - 200 , - 350});*/

	CreateActor<Map_SpacePort>();
	Monster_GunMan* Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 1738 , 7065 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 11027, 7058 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 3186 , 7058 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 5366, 6825 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 5379, 6385 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 7242, 6544 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 8407, 7060 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 9142, 7060 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 10162, 6839 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 12827, 6384 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 15259, 3932 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 15521, 5371 });
	Monster = CreateActor<Monster_GunMan>(ZORDER::MONSTER);
	Monster->SetPos({ 15544, 7073 });

	Ladder* NewLadder = CreateActor<Ladder>(ZORDER::OBJECT);
	NewLadder->SetPos({ 15945, 6492 });
	// NewLadder->SetPos(m_Player->GetPos() + float4{ 300 , -500 });
	NewLadder->GetCollider()->SetDebugRenderType(CT_Rect);
	NewLadder->GetCollider()->SetScale({ 150, 850 });
	NewLadder->GetCollider()->SetPosition({ 0, -16 });
	
	Ladder* NewLadder2 = CreateActor<Ladder>(ZORDER::OBJECT);
	NewLadder2->SetPos({ 15004, 5662 });
	NewLadder2->GetCollider()->SetDebugRenderType(CT_Rect);
	NewLadder2->GetCollider()->SetScale({ 150, 400 });
	NewLadder2->GetCollider()->SetPosition({ 0, 0 });

	Ladder* NewLadder3 = CreateActor<Ladder>(ZORDER::OBJECT);
	NewLadder3->SetPos({ 15275, 2620 });
	NewLadder3->GetCollider()->SetDebugRenderType(CT_Rect);
	NewLadder3->GetCollider()->SetScale({ 150, 400 });
	NewLadder3->GetCollider()->SetPosition({ 0, 0 });

	Ladder* NewLadder4 = CreateActor<Ladder>(ZORDER::OBJECT);
	NewLadder4->SetPos({ 15410, 1136 });
	NewLadder4->GetCollider()->SetDebugRenderType(CT_Rect);
	NewLadder4->GetCollider()->SetScale({ 150, 250 });
	NewLadder4->GetCollider()->SetPosition({ 0, 0 });

	Object_Door* NewDoor = CreateActor<Object_Door>(ZORDER::OBJECT);
	NewDoor->SetPos(m_Player->GetPos() + float4{ 200 , 0 });
	
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
