#include "Select_BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"
Select_BackGround::Select_BackGround()
{
}

Select_BackGround::~Select_BackGround()
{
}

// 얘를 출력해줄 녀석을 만들어야함 
void Select_BackGround::Start()
{
	GameEngineRender* Render = CreateRender("player_select.bmp", RENDERORDER::BACKGROUND);
	Render->SetScale(GameEngineWindow::GetScreenSize());
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
}

void Select_BackGround::Update(float _DeltaTime)
{
	
}

void Select_BackGround::Render(float _DeltaTime)
{
	
}
