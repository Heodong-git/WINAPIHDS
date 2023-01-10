#include "Monster_Sigma.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

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
	
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Sigma_Left.bmp");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos - float4{ 50, 50 }, { 150, 150 }, float4::Zero, {103, 100 });
}
