#include <GameEnginePlatform/GameEngineWindow.h>
#include "MegaManCore.h"
#include <MegaManContents/TitleLevel.h>
#include <MegaManContents/SelectLevel.h>
#include <MegaManContents/SpacePortLevel.h>
#include <MegaManContents/EndTitleLevel.h>

// static 변수 구현
MegaManCore MegaManCore::Core;

MegaManCore::MegaManCore()
{
}

MegaManCore::~MegaManCore()
{
}

// 게임이 실행될 때는 필요한 레벨을 만들어서 Core 클래스의 맵에 모두 저장해둔다.
void MegaManCore::Start()
{ 
	GameEngineWindow::SettingWindowSize({ 1280 , 960 });

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<SelectLevel>("SelectLevel");
	CreateLevel<SpacePortLevel>("SpacePortLevel");
	CreateLevel<EndTitleLevel>("EndTitleLevel");
	
	// 실행 시에 반드시 어떤 레벨을 보여줄 것인지 지정한다. 
	ChangeLevel("TitleLevel");
}


void MegaManCore::Update()
{
	
}
void MegaManCore::End()
{

}