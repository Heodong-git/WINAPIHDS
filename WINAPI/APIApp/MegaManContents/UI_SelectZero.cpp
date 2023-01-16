#include "UI_SelectZero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_SelectZero::UI_SelectZero() :
	AnimationRender(nullptr)
{
}

UI_SelectZero::~UI_SelectZero()
{
}

void UI_SelectZero::Start()
{
	SetPos({ 1130, 450 });
	float4 size = GameEngineWindow::GetScreenSize();
	GameEngineRender* Render = CreateRender("select_UI_Zero.bmp", RENDERORDER::UI);
	Render->SetScale({ size * 0.62f });

	Render = CreateRender("select_ui_text_zero.bmp", RENDERORDER::UI_Text);
	Render->SetScale({ 500 * 0.7f, 150 * 0.7f });
	Render->SetPosition({ 150 , 200 });

	AnimationRender = CreateRender(RENDERORDER::PLAYER);
	AnimationRender->SetScale({ 165,200 });
	AnimationRender->SetPosition({ 410, 180 });
	AnimationRender->CreateAnimation({ .AnimationName = "select_zero",  .ImageName = "select_player_attack_left.bmp", .Start = 2, .End = 3 });
	AnimationRender->ChangeAnimation("select_zero");
}

void UI_SelectZero::Update(float _DeltaTime)
{
}

void UI_SelectZero::Render(float _DeltaTime)
{
}
