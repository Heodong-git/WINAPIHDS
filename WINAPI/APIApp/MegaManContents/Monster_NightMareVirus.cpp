#include "Monster_NightMareVirus.h"
#include <GameEnginePlatform/GameEngineWindow.h>

Monster_NightMareVirus::Monster_NightMareVirus()
{
}

Monster_NightMareVirus::~Monster_NightMareVirus()
{
}

// ����Ʈ�޾���̷����� �����Ǹ� �ؾ��� ��
void Monster_NightMareVirus::Start()
{	
	SetPos({ 600, 600 });
}

// ����Ʈ�޾� ���̷��� Ŭ������ ���� ����
void Monster_NightMareVirus::Update()
{
}

// ������ ���� ȭ�鿡 ��� ����� ������. 
// ���� ������ �������� ��ġ�� �޾ƿ���.
// �� ��ġ�� �������� ���� 80, ���� 80 ũ��� �簢���� �׸���. 
void Monster_NightMareVirus::Render()
{
	float4 MonsterPos = GetPos();

	Rectangle(GameEngineWindow::GetDrawHdc(),
		MonsterPos.ix() - 40,
		MonsterPos.iy() - 40,
		MonsterPos.ix() + 40,
		MonsterPos.iy() + 40);
}
