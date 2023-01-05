#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"

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
	CreateActor<Player_Zero>();
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
}

void SigmaStageLevel::Update()
{

}
