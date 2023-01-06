#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include <GameEngineBase/GameEngineDirectory.h>


SigmaStageLevel::SigmaStageLevel()
{
}

SigmaStageLevel::~SigmaStageLevel()
{
}

// �������� �ʿ��� �͵��� �����.
// ������������ �ʿ��� ��
// 1. ��¥��
// 2. �÷��̾�
// 3. ����
// 4. ��ֹ�
// 5. ������
// 6. �÷��̾� HP�� 
// 7. ���� HP�� 
void SigmaStageLevel::Loading()
{
	// �̹����ε�
	// ���͸� ��ü���� , ���͸��� Path Ŭ������ ����
	GameEngineDirectory Directory;
	
	// ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	
	// ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");

	// ������ο� �ִ� �ش� ���ϸ��� �ٿ��ش�. �����ʿ��Լ�
	//Directory.GetPlusFileName("player_recall.bmp");

	CreateActor<Player_Zero>();
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
}

void SigmaStageLevel::Update()
{

}
