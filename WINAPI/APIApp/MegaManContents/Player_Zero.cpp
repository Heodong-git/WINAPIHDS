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
	// 플레이어의 위치를 세팅한다.
	SetPos({ 50, 50 });
	
}

void Player_Zero::Update()
{
	// 업데이트, 화면에서 보여질 플레이어의 위치 등을 연산한다.
	// SetMove({ float4::Right * 0.001f});
}

void Player_Zero::Render()
{
	// Update에서 연산된 값을 활용하여 화면에 출력한다.
	float4 PlayerPos = GetPos();

	// 1. 이미지를 찾는다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("player_recall.bmp");
	
	// 2.  현재 백버퍼의 이미지의 BitCopy 함수를 호출하여
	// 백버퍼의  특정 위치에 플레이어의 이미지를 복사한다. 
	GameEngineWindow::GetBackBufferImage()->BitCopy(Image, PlayerPos - float4{ 50, 50 }, { 200.0f, 200.0f });
}
