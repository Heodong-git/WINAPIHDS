#include "SigmaStage_BackGround.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

SigmaStage_BackGround::SigmaStage_BackGround()
{
}

SigmaStage_BackGround::~SigmaStage_BackGround()
{
}

void SigmaStage_BackGround::Start()
{
	// �̳༮�� Setpos �� ���� �ʿ����
	// �������� Setpositon �� �ֱ� ����.
	// ���� ���߾��� ��ġ�� ��ǥ�� ��´�.
	SetPos(GameEngineWindow::GetScreenSize().half());
	GameEngineRender* Render = CreateRender("sigmastage_background.bmp", RENDERORDER::BACKGROUND);
	Render->SetScale(GameEngineWindow::GetScreenSize());
}

void SigmaStage_BackGround::Update(float _DeltaTime)
{

}

void SigmaStage_BackGround::Render(float _DeltaTime)
{
	
}
