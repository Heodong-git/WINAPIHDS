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
	SetPos({ 350, 400 });
	
}

// 플레이어 연산
void Player_Zero::Update()
{
	SetMove({ float4::Left * 0.1f});
}

void Player_Zero::Render()
{
	// Update에서 연산된 값을 활용하여 화면에 출력한다.
	float4 PlayerPos = GetPos();

	// 1. 이미지를 찾는다. 
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("player_recall.bmp");
	
	// 2.  현재 백버퍼의 이미지의 TransCopy 함수를 호출하여
	// 백버퍼의  특정 위치에 플레이어의 이미지를 복사한다. 
	
	// TransCopy (이미지, 복사될 위치, 복사될 크기, 이미지의 어느위치부터 복사할건지, 그 위치부터 얼만큼의 크기로 복사될건지
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos - float4{ 50, 50 }, { 130, 130 }, {526 , 293}, {145, 141});
}
