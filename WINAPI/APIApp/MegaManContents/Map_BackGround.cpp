#include "Map_BackGround.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>

Map_BackGround::Map_BackGround()
{
}

Map_BackGround::~Map_BackGround()
{
}

void Map_BackGround::Start()
{
	SetPos(float4{ 0 , 0 });
}

void Map_BackGround::Update()
{
}

void Map_BackGround::Render()
{
	float4 MapPos = GetPos();

	// 1. �̹����� ã�´�. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Sigma_Stage.bmp");

	// 2.  ���� ������� �̹����� TransCopy �Լ��� ȣ���Ͽ�
	// �������  Ư�� ��ġ�� �÷��̾��� �̹����� �����Ѵ�. 

	// TransCopy ( ����� ��ġ, ����� ũ�� / �̹����� �����ġ���� �����Ұ���, �̹����� ������ �����Ұ��� ) 
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MapPos, { 1360, 768 },
														float4{ 8 , 1284 }, { 517, 250 });
}
