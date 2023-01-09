#include <GameEnginePlatform/GameEngineWindow.h>
#include "MegaManCore.h"
#include <MegaManContents/TitleLevel.h>
#include <MegaManContents/SelectLevel.h>
#include <MegaManContents/SigmaStageLevel.h>
#include <MegaManContents/EndTitleLevel.h>

// static ���� ����
MegaManCore MegaManCore::Core;

MegaManCore::MegaManCore()
{
}

MegaManCore::~MegaManCore()
{
}

// ������ ����� ���� �ʿ��� ������ ���� Core Ŭ������ �ʿ� ��� �����صд�.
void MegaManCore::Start()
{ 
	// �����찡 ������ �� �̹� �ػ󵵸� �����. 	
	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<SelectLevel>("SelectLevel");
	CreateLevel<SigmaStageLevel>("SigmaStageLevel");
	CreateLevel<EndTitleLevel>("EndTitleLevel");
	
	// ���� �ÿ� �ݵ�� � ������ ������ ������ �����Ѵ�. 
	ChangeLevel("SigmaStageLevel");
}


void MegaManCore::Update()
{
	
}
void MegaManCore::End()
{

}