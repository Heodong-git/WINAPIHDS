#include "MegaManCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "TitleLevel.h"
#include "SelectLevel.h"
#include "SpacePortLevel.h"
#include "EndTitleLevel.h"
#include "ImageTestLevel.h"

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