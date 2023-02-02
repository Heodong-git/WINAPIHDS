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

void Select_BackGround::Start()
{
	m_Render = CreateRender("select_background.bmp", ZORDER::BACKGROUND);
	m_Render->SetScale(GameEngineWindow::GetScreenSize());
	m_Render->SetPosition(GameEngineWindow::GetScreenSize().half());
}

void Select_BackGround::Update(float _DeltaTime)
{
	
}

void Select_BackGround::Render(float _DeltaTime)
{
	
}
