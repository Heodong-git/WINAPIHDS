#include "UI_SelectX.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_SelectX::UI_SelectX()
{
}

UI_SelectX::~UI_SelectX()
{
}

void UI_SelectX::Start()
{
	float4 size = GameEngineWindow::GetScreenSize();
	
	GameEngineRender* Render = CreateRender("select_UI_X.bmp", RENDERORDER::UI);
	Render->SetScale({ size * 0.62f });
	Render->SetPosition({ 480, 450 });
}

void UI_SelectX::Update(float _DeltaTime)
{
}

void UI_SelectX::Render(float _DeltaTime)
{
}
