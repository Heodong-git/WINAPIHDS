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
	// NewLadder->SetPos({ 15945, 6492 });
	NewLadder->SetPos(m_Player->GetPos() + float4{ 300 , -500 });
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
