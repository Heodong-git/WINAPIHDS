#include "Ladder.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player_Zero.h"
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
}

void Ladder::Render(float _DeltaTime)
{
	// ������
	HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

	// ��ġ�����ʿ�
	// 15949, 6492 
	float4 ActorPos = GetPos() - GetLevel()->GetCameraPos();

	Rectangle(DoubleDC,
		ActorPos.ix() - 5,
		ActorPos.iy() - 5,
		ActorPos.ix() + 5,
		ActorPos.iy() + 5
	);
}

void Ladder::Update(float _DeltaTime)
{
	
}
