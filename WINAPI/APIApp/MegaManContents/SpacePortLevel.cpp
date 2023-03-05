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
#include "ContentsEnum.h"

SpacePortLevel::SpacePortLevel()
{
}

SpacePortLevel::~SpacePortLevel()
{
}
 
void SpacePortLevel::Loading()
{
	// 이미지로드
	ImageLoad();
	// 사운드로드
	SoundLoad();
	// 액터로드
	ActorLoad();
	// 카메라로드
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

	// q 키가 눌렸다면 디버그모드 on , off 
	if (GameEngineInput::IsDown("DebugRenderSwitch"))
	{
		DebugRenderSwitch();
	}

	// 카메라가 지정위치에 도착했다면 섹션클리어를 true 로 변경하여 아래 코드가 동작하지 않도록 처리한다. 
	if (true == m_SectionClear)
	{
		return; 
	}
	// 여기서는 플레이어의 위치를 체크한다.
	// 플레이어가 해당 값의 위치를 넘어섰다면 위로 올라가는 구역에 도착한 것이기 때문에 true 로 변경
	if (GetCameraPos().x > 14800.0f)
	{
		m_HeightSection = true;
		m_FirstSection = true;
	}

	// 첫번째 섹션에 도착했을 때 
	// 플레이어의 y축 위치가 현재 카메라의 y축 위치를 넘어섰다면
	// 카메라의 y축 값을 - 시켜서 다음섹션의 카메라 위치까지 이동시킨다. 
	
	// 여기서 플레이어가 마지막섹션까지도착했을때의 좌표를 가져와서 

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
	// 사운드출력
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Spaceport_bgm.wav");
	BGMPlayer.LoopCount(100);
	BGMPlayer.Volume(0.1f);

	m_Player->ChangeState(STATEVALUE::RECALL);
}

void SpacePortLevel::SoundLoad()
{
	// 경로탐색 
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
	// 이미지로딩
	GameEngineDirectory Directory;

	// 1. 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SpacePortLevel");

	{
		// 제로 오른쪽 스프라이트 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_zero_sprite_right.bmp"));
		Image->Cut(12, 16);
	}
	{
		// 제로 왼쪽 스프라이트
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_zero_sprite_left.bmp"));
		Image->Cut(12, 16);
	}
	{
		// UI HpBar
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ui_hp_bar.bmp"));
		Image->Cut(8, 5);
	}

	{
		// 스페이스포트 맵
		// GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort.bmp"));
		GameEngineImage* ColImage = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ColMap_SpacePort.bmp"));
	}
	{
		// 스페이스포트 분할맵 
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_0.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_1.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_2.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_3.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_4.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_5.bmp"));
		Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Map_SpacePort_6.bmp"));
	}

	// 보스 커널
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_colonel_left.bmp"));
		Image->Cut(8, 6);
	}

	// 몬스터

	// gunman image
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_left.bmp"));
		Image->Cut(8, 5);
	}
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("spaceport_gunman_right.bmp"));
		Image->Cut(8, 5);
	}

	// 이펙트
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
	// 해당 레벨에서 사용할 액터 생성
	// 액터 생성시에 인자로 넣어주는 값은 업데이트,렌더링 순서이며 값이 높을 수록 나중에 연산,렌더링이 된다. 
	m_Player = CreateActor<Player_Zero>(ZORDER::PLAYER);
	m_Player->SetPos({ 400, 7060 });
	m_Player->SetStartPos(m_Player->GetPos());
	// 일단 플레이어 애니메이션부터 필요한거 다 진행하고나서 다시. 
	GameEngineActor* Boss = CreateActor<Boss_Colonel>(ZORDER::BOSS);
	Boss->SetPos({ 18587, 968 });

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

	
}
void SpacePortLevel::CameraLoad()
{
	// 카메라 키생성
	if (false == GameEngineInput::IsKey("CameraLeftMove"))
	{
		GameEngineInput::CreateKey("CameraLeftMove", 'A');
		GameEngineInput::CreateKey("CameraRightMove", 'D');
		GameEngineInput::CreateKey("CameraDownMove", 'S');
		GameEngineInput::CreateKey("CameraUpMove", 'W');
	}

	// 디버그렌더 스위치 생성
	if (false == GameEngineInput::IsKey("DebugRenderSwitch"))
	{
		GameEngineInput::CreateKey("DebugRenderSwitch", '2');
	}

	// 여기서 카메라 위치 고정은 됐어
	m_StartCameraPos = GameEngineWindow::GetScreenSize().half() + float4{ -580 , 5760 };
	SetCameraMove(m_StartCameraPos);
}
// 코어 -> 레벨생성
// 레벨 -> 레벨 안에서 사용할 액터 생성, 생성 후 AcotrStart
// 액터 -> 액터가 생성되고 나서 기본적으로 필요한 부분 수행

// 코어 : 소유한 레벨의 Update, Render 수행 후, 백버퍼에 더블버퍼에 출력된 이미지를 옮겨준다. 
// 레벨 : 소유한 액터의 Update, Render 수행을 담당
// 액터 : 
