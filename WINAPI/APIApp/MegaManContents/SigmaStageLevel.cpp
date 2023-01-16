#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include "SigmaStage_BackGround.h"
#include "UI_PlayerHpBar.h"

SigmaStageLevel::SigmaStageLevel()
{
}

SigmaStageLevel::~SigmaStageLevel()
{
}

// 레벨에서 필요한 것들을 만든다.
// 스테이지에서 필요한 것
// 1. 통짜맵
// 2. 플레이어
// 3. 몬스터
// 4. 장애물
// 5. 아이템
// 6. 플레이어 HP바 
// 7. 보스 HP바 
void SigmaStageLevel::Loading()
{
	// 이미지로딩
	GameEngineDirectory Directory;
	
	// 1. 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SigmaStage");

	{
		//// 3. 사용할 이미지 로드 후 Cut, 잠깐 주석 
		//GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
		//Image->Cut({ 56, 279 }, { 1211,440 }, 9, 1);
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
		Image->Cut({ 56, 276 }, { 1208, 440 }, 9, 1);
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_left.bmp"));
		Image->Cut({ 7, 11 }, { 500, 100 }, 5, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("monster_metal_t_left.bmp"));
		Image->Cut({ 18, 118 }, { 605, 196 }, 8, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_Stage.bmp"));
		Image->Cut({ 7, 1543 }, { 294, 1794 }, 1, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ui_hp_bar.bmp"));
		Image->Cut({ 40, 28 }, { 96 , 212 }, 1, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Monster_NightMare_Virus_left.bmp"));
		Image->Cut({ 57, 11 }, { 534 , 124 }, 3, 1);
	}

	// 해당 레벨에서 사용할 액터 생성
	// 액터 생성시에 인자로 넣어주는 값은 업데이트,렌더링 순서이며 값이 높을 수록 나중에 연산,렌더링이 된다. 
	CreateActor<Player_Zero>();
	CreateActor<SigmaStage_BackGround>();
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
	CreateActor<UI_PlayerHpBar>();
}

void SigmaStageLevel::Update(float _DeltaTime)
{
	
}
// 코어 -> 레벨생성
// 레벨 -> 레벨 안에서 사용할 액터 생성, 생성 후 AcotrStart
// 액터 -> 액터가 생성되고 나서 기본적으로 필요한 부분 수행

// 코어 : 소유한 레벨의 Update, Render 수행 후, 백버퍼에 더블버퍼에 출력된 이미지를 옮겨준다. 
// 레벨 : 소유한 액터의 Update, Render 수행을 담당
// 액터 : 

// 액터생성시 
// 백그라운드 0
// 맵 1
// 몬스터 2
// 플레이어 일단 10 