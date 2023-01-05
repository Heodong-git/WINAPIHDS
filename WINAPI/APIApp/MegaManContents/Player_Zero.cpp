#include "Player_Zero.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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

}

void Player_Zero::Render()
{
	// Update���� ����� ���� Ȱ���Ͽ� ȭ�鿡 ����Ѵ�.
	float4 PlayerPos = GetPos();

	// ����, ���� 100, 100 �������� �÷��̾� 
	Rectangle(GameEngineWindow::GetDrawHdc(), 
		PlayerPos.ix() - 50, 
		PlayerPos.iy() - 50,
		PlayerPos.ix() + 50, 
		PlayerPos.iy() + 50);
}
