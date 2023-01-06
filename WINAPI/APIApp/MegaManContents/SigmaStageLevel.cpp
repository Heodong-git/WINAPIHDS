#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include <GameEngineBase/GameEngineDirectory.h>


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
	// 디렉터리 객체생성 , 디렉터리는 Path 클래스를 소유
	GameEngineDirectory Directory;
	
	// 상위폴더에 해당 디렉터리가 있는지 확인
	Directory.MoveParentToDirectory("ContentsResources");
	
	// 디렉터리가 있다면 경로를 설정해준다.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");

	// 최종경로에 있는 해당 파일명을 붙여준다. 
	//Directory.GetPlusFileName("player_recall.bmp");

	CreateActor<Player_Zero>();
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
}

void SigmaStageLevel::Update()
{

}
