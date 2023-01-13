#include "Title_BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"


Title_BackGround::Title_BackGround()
{
}

Title_BackGround::~Title_BackGround()
{
}

void Title_BackGround::Start()
{
	GameEngineRender* Render = CreateRender("Main_Title.bmp", RENDERORDER::BACKGROUND);
	Render->SetScale(GameEngineWindow::GetScreenSize());
	Render->SetPosition(GameEngineWindow::GetScreenSize().half());
}

void Title_BackGround::Update(float _DeltaTime)
{
}

void Title_BackGround::Render(float _DeltaTime)
{
}
