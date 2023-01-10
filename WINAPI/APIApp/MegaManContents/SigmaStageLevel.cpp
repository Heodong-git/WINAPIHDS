#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
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
	// �̹����ε�
	// ���͸� ��ü���� , ���͸��� ��θ� ������ ����.
	GameEngineDirectory Directory;
	
	// 1. ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");

	// 3. �ϼ��� ��ο� ���ϸ��� �ٿ� ������θ� �ϼ��Ѵ�. 
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_Left.bmp"));
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Monster_Metal_T_Left.bmp"));
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Monster_NightMare_Virus_Left.bmp"));

	// �ش� �������� ����� ���� ����
	CreateActor<Player_Zero>(1);
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
}

void SigmaStageLevel::Update()
{

}
