#include "Player_Zero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineResources.h>

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

void Player_Zero::Start()
{
	// �÷��̾��� ��ġ�� �����Ѵ�.
	SetPos({ 50, 50 });
	
}

void Player_Zero::Update()
{
	// ������Ʈ, ȭ�鿡�� ������ �÷��̾��� ��ġ ���� �����Ѵ�.
	// SetMove({ float4::Right * 0.001f});
}

void Player_Zero::Render()
{
	// Update���� ����� ���� Ȱ���Ͽ� ȭ�鿡 ����Ѵ�.
	float4 PlayerPos = GetPos();

	// 1. �̹����� ã�´�. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("player_recall.bmp");
	
	// 2.  ���� ������� �̹����� BitCopy �Լ��� ȣ���Ͽ�
	// �������  Ư�� ��ġ�� �÷��̾��� �̹����� �����Ѵ�. 
	GameEngineWindow::GetBackBufferImage()->BitCopy(Image, PlayerPos - float4{ 50, 50 }, { 200.0f, 200.0f });
}
