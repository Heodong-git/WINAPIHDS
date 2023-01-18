#include "SigmaStage_BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

SigmaStage_BackGround::SigmaStage_BackGround()
{
}

SigmaStage_BackGround::~SigmaStage_BackGround()
{
}

void SigmaStage_BackGround::Start()
{
	// 이녀석은 Setpos 가 굳이 필요없음
	// 렌더러의 Setpositon 이 있기 때문.
	// 맵의 정중앙의 위치를 좌표로 잡는다.
	SetPos(GameEngineWindow::GetScreenSize().half());
	GameEngineRender* Render = CreateRender("sigmastage_background.bmp", RENDERORDER::BACKGROUND);
	Render->SetScale(GameEngineWindow::GetScreenSize());
}

void SigmaStage_BackGround::Update(float _DeltaTime)
{

}

void SigmaStage_BackGround::Render(float _DeltaTime)
{
	
}
