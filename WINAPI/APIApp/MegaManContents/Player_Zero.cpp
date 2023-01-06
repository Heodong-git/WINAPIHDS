#include "Player_Zero.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineMath.h>

Player_Zero::Player_Zero()
{
}

Player_Zero::~Player_Zero()
{
}

void Player_Zero::Start()
{
	// 플레이어의 위치를 세팅한다.
	SetPos({ 50, 50 });
	
}

void Player_Zero::Update()
{
	// 업데이트, 화면에서 보여질 플레이어의 위치 등을 연산한다.
	SetMove({ float4::Right * 0.001f});

}

void Player_Zero::Render()
{
	// Update에서 연산된 값을 활용하여 화면에 출력한다.
	float4 PlayerPos = GetPos();

	// 가로, 세로 100, 100 사이즈의 플레이어 
	Rectangle(GameEngineWindow::GetDrawHdc(), 
		PlayerPos.ix() - 50, 
		PlayerPos.iy() - 50,
		PlayerPos.ix() + 50, 
		PlayerPos.iy() + 50);
}
