#include "Monster_Sigma.h"
#include <GameEnginePlatform/GameEngineWindow.h>

Monster_Sigma::Monster_Sigma()
{
}

Monster_Sigma::~Monster_Sigma()
{
}

// Ŭ���� ������ Ŭ������ �������� �͵�, �ʿ��� �͵��� �� �Լ����� ������ش�. 
void Monster_Sigma::Start()
{
	SetPos({ 400, 400 });
}

// Ŭ������ �ʿ��� �������
void Monster_Sigma::Update()
{
}

// ������ �Ϸ�� �� �� ���� ���� ȭ�鿡 ��� 
void Monster_Sigma::Render()
{
	float4 MonsterPos = GetPos();
	Rectangle(GameEngineWindow::GetDrawHdc(),
		MonsterPos.ix() - 50,
		MonsterPos.iy() - 50,
		MonsterPos.ix() + 50,
		MonsterPos.iy() + 50);
}
