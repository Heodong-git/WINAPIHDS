#include "UI_BottomText_PlayerSelect.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

float UI_BottomText_PlayerSelect::Time = 0.0f;

UI_BottomText_PlayerSelect::UI_BottomText_PlayerSelect() :
	MoveSpeed(400.0f),
	AnimationRender(nullptr)
{
}

UI_BottomText_PlayerSelect::~UI_BottomText_PlayerSelect()
{
}

void UI_BottomText_PlayerSelect::Start()
{
	SetPos({ -300, 820 });
	OriginPos = GetPos();
	float4 size = GameEngineWindow::GetScreenSize();
	AnimationRender = CreateRender("select_ui_text_playerselect.bmp", RENDERORDER::UI_Text);
	AnimationRender->SetScale({ size.x * 0.5f, size.y * 0.16f });
}

void UI_BottomText_PlayerSelect::Update(float _DeltaTime)
{
	Time += _DeltaTime;

	if (6.2f <= Time)
	{
		SetPos(OriginPos);
		Time = 0.0f;
		return;
	}

	if (6.1f >= Time)
	{
		SetMove({ float4::Right * MoveSpeed * _DeltaTime });
	}
}

void UI_BottomText_PlayerSelect::Render(float _DeltaTime)
{
}
