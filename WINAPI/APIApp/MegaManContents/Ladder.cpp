#include "Ladder.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Start()
{
	m_Collider = CreateCollision(COLORDER::OBJECT);
	m_Collider->SetScale({ 50, 500 });
	m_Collider->SetDebugRenderType(CT_Rect);
}

void Ladder::Render(float _DeltaTime)
{
	// 디버깅용
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	// 위치세팅필요
	// 15949, 6492 
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}
