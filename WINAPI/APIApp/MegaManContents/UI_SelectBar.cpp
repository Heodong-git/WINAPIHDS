#include "UI_SelectBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "SelectLevel.h"
#include "ContentsEnum.h"

UI_SelectBar::UI_SelectBar() :
	AnimationRender(nullptr)
{
}

UI_SelectBar::~UI_SelectBar()
{
}


void UI_SelectBar::Start()
{
	SetPos({ 1110 , 450 });
	AnimationRender = CreateRender(RENDERORDER::UI);
	AnimationRender->SetScale({1050 , 600});
	AnimationRender->CreateAnimation({ .AnimationName = "select_bar", .ImageName = "select_select_bar.bmp", .Start = 0, .End = 2 });
	AnimationRender->ChangeAnimation("select_bar");
}

void UI_SelectBar::Update(float _DeltaTime)
{
}

void UI_SelectBar::Render(float _DeltaTime)
{
}
