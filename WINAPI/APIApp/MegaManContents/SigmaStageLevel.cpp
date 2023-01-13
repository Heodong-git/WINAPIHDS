#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCore.h>
#include "SigmaStageLevel.h"
#include "Player_Zero.h"
#include "Monster_Sigma.h"
#include "Monster_NightMareVirus.h"
#include "Monster_MetalT.h"
#include "SigmaStage_BackGround.h"
#include "UI_PlayerHpBar.h"

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
	GameEngineDirectory Directory;
	
	// 1. ���������� �ش� ���͸��� �ִ��� Ȯ��
	Directory.MoveParentToDirectory("ContentsResources");
	// 2. ���͸��� �ִٸ� ��θ� �������ش�.  
	Directory.Move("ContentsResources");
	Directory.Move("Image");
	Directory.Move("SigmaStage");

	{
		//// 3. ����� �̹��� �ε� �� Cut, ��� �ּ� 
		//GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
		//Image->Cut({ 56, 279 }, { 1211,440 }, 9, 1);
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("player_recall.bmp"));
		Image->Cut({ 536, 291 }, { 662,439 }, 1, 1);
	}
	
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_left.bmp"));
		Image->Cut({ 7, 11 }, { 500, 100 }, 5, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("monster_metal_t_left.bmp"));
		Image->Cut({ 71, 22 }, { 520, 90 }, 6, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Sigma_Stage.bmp"));
		Image->Cut({ 7, 1543 }, { 294, 1794 }, 1, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("ui_hp_bar.bmp"));
		Image->Cut({ 40, 28 }, { 96 , 212 }, 1, 1);
	}

	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Directory.GetPlusFileName("Monster_NightMare_Virus_left.bmp"));
		Image->Cut({ 45, 6 }, { 215 , 138 }, 1, 1);
	}

	// �ش� �������� ����� ���� ����
	// ���� �����ÿ� ���ڷ� �־��ִ� ���� ������Ʈ,������ �����̸� ���� ���� ���� ���߿� ����,�������� �ȴ�. 
	CreateActor<Player_Zero>();
	CreateActor<SigmaStage_BackGround>();
	CreateActor<Monster_Sigma>();
	CreateActor<Monster_NightMareVirus>();
	CreateActor<Monster_MetalT>();
	CreateActor<UI_PlayerHpBar>();
}

void SigmaStageLevel::Update(float _DeltaTime)
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