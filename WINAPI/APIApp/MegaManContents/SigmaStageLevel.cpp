#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include "Map_BackGround.h"

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
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_Stage.bmp"));
	GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Mr_X_Stage.bmp"));
	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	CreateActor<Player_Zero>(10);
	CreateActor<Map_BackGround>();
	CreateActor<Monster_Sigma>(0);
	CreateActor<Monster_NightMareVirus>(0);
	CreateActor<Monster_MetalT>(0);
}

void SigmaStageLevel::Update()
{

}

// �ھ� -> ��������
// ���� -> ���� �ȿ��� ����� ���� ����, ���� �� AcotrStart
// ���� -> ���Ͱ� �����ǰ� ���� �⺻������ �ʿ��� �κ� ����

// �ھ� : ������ ������ Update, Render ���� ��, ����ۿ� ������ۿ� ��µ� �̹����� �Ű��ش�. 
// ���� : ������ ������ Update, Render ������ ���
// ���� : 

// ���ͻ����� 
// ��׶��� 0
// �� 1
// ���� 2
// �÷��̾� �ϴ� 10 