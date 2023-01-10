#include "Monster_NightMareVirus.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

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

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_NightMare_Virus_Left.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos - float4{ 50, 50 }, { 100, 100 }, {60, 0}, { 140, 140 });
}
