#include "Monster_Sigma.h"
#include <GameEnginePlatform/GameEngineWindow.h>

Monster_Sigma::Monster_Sigma()
{
}

Monster_Sigma::~Monster_Sigma()
{
}

// 클래스 생성시 클래스가 가져야할 것들, 필요한 것들을 이 함수에서 만들어준다. 
void Monster_Sigma::Start()
{
	SetPos({ 400, 400 });
}

// 클래스에 필요한 연산수행
void Monster_Sigma::Update()
{
}

// 연산이 완료된 후 그 값을 토대로 화면에 출력 
void Monster_Sigma::Render()
{
	float4 MonsterPos = GetPos();
	Rectangle(GameEngineWindow::GetDrawHdc(),
		MonsterPos.ix() - 50,
		MonsterPos.iy() - 50,
		MonsterPos.ix() + 50,
		MonsterPos.iy() + 50);
}
