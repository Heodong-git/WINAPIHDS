#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"

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
void SigmaStageLevel::Loading()
{
	CreateActor<Player_Zero>();
	CreateActor<Monster_Sigma>();
}

void SigmaStageLevel::Update()
{

}
