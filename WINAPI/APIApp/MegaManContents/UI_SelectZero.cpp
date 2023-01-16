#include "UI_SelectZero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_SelectZero::UI_SelectZero()
{
}

UI_SelectZero::~UI_SelectZero()
{
}

void UI_SelectZero::Start()
{
	float4 size = GameEngineWindow::GetScreenSize();
	GameEngineRender* Render = CreateRender("select_UI_Zero.bmp", RENDERORDER::UI);
	Render->SetScale({ size * 0.62f });
	Render->SetPosition({ 1130, 450 });
}

void UI_SelectZero::Update(float _DeltaTime)
{
}

void UI_SelectZero::Render(float _DeltaTime)
{
}
