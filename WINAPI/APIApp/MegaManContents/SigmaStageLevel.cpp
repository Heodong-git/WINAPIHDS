#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"

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
void SigmaStageLevel::Loading()
{
	CreateActor<Player_Zero>();
	CreateActor<Monster_Sigma>();
}

void SigmaStageLevel::Update()
{

}
