#include "UI_PlayerHpBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

UI_PlayerHpBar::UI_PlayerHpBar()
{
}

UI_PlayerHpBar::~UI_PlayerHpBar()
{
}

// 스타트에서 렌더러 생성
void UI_PlayerHpBar::Start()
{
	SetPos(float4{ 130, 220 });
	GameEngineRender* Render = CreateRender("ui_hp_bar.bmp", RENDERORDER::UI);
	Render->SetScale({ 130, 350 });
}

void UI_PlayerHpBar::Update(float _DeltaTime)
{
}

void UI_PlayerHpBar::Render(float _DeltaTime)
{
}
