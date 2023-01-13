#include "Monster_Sigma.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Monster_Sigma::Monster_Sigma()
{
}

Monster_Sigma::~Monster_Sigma()
{
}

// Ŭ���� ������ Ŭ������ �������� �͵�, �ʿ��� �͵��� �� �Լ����� ������ش�. 
void Monster_Sigma::Start()
{
	SetPos({ 1200, 350 });

	// �������� , ������ ����� �̹���, Zorder �� �Է�
	GameEngineRender* Render = CreateRender("Sigma_left.bmp", RENDERORDER::MONSTER);
	// �������� x�� y���� ũ�⼳��
	Render->SetScale({ 200, 200 });
}

// Ŭ������ �ʿ��� �������
void Monster_Sigma::Update(float _DeltaTime)
{
}

// ������ �Ϸ�� �� �� ���� ���� ȭ�鿡 ��� 
void Monster_Sigma::Render(float _DeltaTime)
{
	/*float4 MonsterPos = GetPos();
	
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Sigma_Left.bmp");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 150, 150 }, float4::Zero, {103, 100 });*/
}
