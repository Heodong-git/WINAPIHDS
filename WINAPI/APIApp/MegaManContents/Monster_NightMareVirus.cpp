#include "Monster_NightMareVirus.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

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

	GameEngineRender* Render = CreateRender("Monster_NightMare_Virus_left.bmp", RENDERORDER::MONSTER);
	Render->SetScale({200, 200});
}

// ����Ʈ�޾� ���̷��� Ŭ������ ���� ����
void Monster_NightMareVirus::Update(float _DeltaTime)
{
}

// ������ ���� ȭ�鿡 ��� ����� ������. 
// ���� ������ �������� ��ġ�� �޾ƿ���.
// �� ��ġ�� �������� ���� 80, ���� 80 ũ��� �簢���� �׸���. 
void Monster_NightMareVirus::Render(float _DeltaTime)
{
	/*float4 MonsterPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Monster_NightMare_Virus_Left.bmp");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 100, 100 }, {60, 0}, { 140, 140 });*/
}
