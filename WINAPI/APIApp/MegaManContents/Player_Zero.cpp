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
	SetPos({ 100, 400 });
	
}

// �÷��̾� ����
void Player_Zero::Update()
{
	SetMove({ float4::Right * 0.1f});
}

void Player_Zero::Render()
{
	// Update���� ����� ���� Ȱ���Ͽ� ȭ�鿡 ����Ѵ�.
	// �÷��̾��� ���� ��ġ�� �޾ƿ´�. 
	float4 PlayerPos = GetPos();

	// 1. �̹����� ã�´�. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("player_recall.bmp");
	
	// 2.  ���� ������� �̹����� TransCopy �Լ��� ȣ���Ͽ�
	// �������  Ư�� ��ġ�� �÷��̾��� �̹����� �����Ѵ�. 
	
	// TransCopy ( ����� ��ġ, ����� ũ�� / �̹����� �����ġ���� �����Ұ���, �̹����� ������ �����Ұ��� ) 
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos -	float4::Zero, { 130, 130 }, 
		                                                                   float4{526 , 293}, {145, 141});
}
