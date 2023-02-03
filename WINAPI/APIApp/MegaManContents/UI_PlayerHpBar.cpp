#include "UI_PlayerHpBar.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"

UI_PlayerHpBar::UI_PlayerHpBar()
{
}

UI_PlayerHpBar::~UI_PlayerHpBar()
{
}

// ��ŸƮ���� ������ ����
void UI_PlayerHpBar::Start()
{
	m_AnimationRender = CreateRender(ZORDER::UI);
	m_AnimationRender->SetScale({ 320 * 3.0f , 240 * 3.0f });

	// ������ʹٽ�. 
	// ī�޶� �����̸� ī�޶�� �Ȱ��� �̵��ϸ� �ɵ�. 
	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 0 , .End = 35 , .InterTime = 0.6f });
	
	/*m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 1 , .End = 1 , .InterTime = 0.6f });

	m_AnimationRender->CreateAnimation({ .AnimationName = "Player_HpbarMax" , .ImageName = "ui_hp_bar.bmp" ,
								.Start = 2 , .End = 2 , .InterTime = 0.6f });*/

	m_AnimationRender->ChangeAnimation("Player_HpbarMax");
}

void UI_PlayerHpBar::Update(float _DeltaTime) 
{
	
}

void UI_PlayerHpBar::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
