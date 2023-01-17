#include "UI_SelectX.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>
#include "ContentsEnum.h"

UI_SelectX::UI_SelectX()
{
}

UI_SelectX::~UI_SelectX()
{
}

void UI_SelectX::Start()
{
	SetPos({ 480,450 });
	float4 size = GameEngineWindow::GetScreenSize();
	
	GameEngineRender* Render = CreateRender("select_UI_X.bmp", RENDERORDER::UI);
	Render->SetScale({ size * 0.62f });

	Render = CreateRender("select_ui_text_x.bmp", RENDERORDER::UI_Text);
	Render->SetScale({ 600 * 0.8f, 150 *0.8f });
	Render->SetPosition({ -50 , 200 });
}

void UI_SelectX::Update(float _DeltaTime)
{
	
}

void UI_SelectX::Render(float _DeltaTime)
{
}
