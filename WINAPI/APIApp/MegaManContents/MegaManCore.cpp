#include <GameEnginePlatform/GameEngineWindow.h>
#include "MegaManCore.h"
#include <MegaManContents/TitleLevel.h>
#include <MegaManContents/SelectLevel.h>
#include <MegaManContents/SpacePortLevel.h>
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
	GameEngineWindow::SettingWindowSize({ 1280 , 960 });

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<SelectLevel>("SelectLevel");
	CreateLevel<SpacePortLevel>("SpacePortLevel");
	CreateLevel<EndTitleLevel>("EndTitleLevel");
	
	// ���� �ÿ� �ݵ�� � ������ ������ ������ �����Ѵ�. 
	ChangeLevel("TitleLevel");
}


void MegaManCore::Update()
{
	
}
void MegaManCore::End()
{

}