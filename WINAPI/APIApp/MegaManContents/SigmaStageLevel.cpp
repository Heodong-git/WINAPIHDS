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
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_right.bmp"));
		Image->Cut( 5 , 5 );
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_idle_walk_left.bmp"));
		Image->Cut(5, 5);
	}

	// 해당 레벨에서 사용할 액터 생성
	// 액터 생성시에 인자로 넣어주는 값은 업데이트,렌더링 순서이며 값이 높을 수록 나중에 연산,렌더링이 된다. 
	CreateActor<Player_Zero>();
	//CreateActor<SigmaStage_BackGround>();
}

void SigmaStageLevel::Update(float _DeltaTime)
{
	
}

void SigmaStageLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}
// 코어 -> 레벨생성
// 레벨 -> 레벨 안에서 사용할 액터 생성, 생성 후 AcotrStart
// 액터 -> 액터가 생성되고 나서 기본적으로 필요한 부분 수행

// 코어 : 소유한 레벨의 Update, Render 수행 후, 백버퍼에 더블버퍼에 출력된 이미지를 옮겨준다. 
// 레벨 : 소유한 액터의 Update, Render 수행을 담당
// 액터 : 
