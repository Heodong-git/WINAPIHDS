#include "Monster_Sigma.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnum.h"

Monster_Sigma::Monster_Sigma()
{
}

Monster_Sigma::~Monster_Sigma()
{
}

// 클래스 생성시 클래스가 가져야할 것들, 필요한 것들을 이 함수에서 만들어준다. 
void Monster_Sigma::Start()
{
	SetPos({ 1200, 350 });

	// 렌더생성 , 생성시 사용할 이미지, Zorder 값 입력
	GameEngineRender* Render = CreateRender("Sigma_left.bmp", RENDERORDER::MONSTER);
	// 렌더링시 x축 y축의 크기설정
	Render->SetScale({ 200, 200 });
}

// 클래스에 필요한 연산수행
void Monster_Sigma::Update(float _DeltaTime)
{
}

// 연산이 완료된 후 그 값을 토대로 화면에 출력 
void Monster_Sigma::Render(float _DeltaTime)
{
	/*float4 MonsterPos = GetPos();
	
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("Sigma_Left.bmp");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, MonsterPos, { 150, 150 }, float4::Zero, {103, 100 });*/
}
