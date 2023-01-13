#include "GameEngineRender.h"
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

// 출력시 사용할 이미지 세팅
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	// 게임엔진 리소스 클래스에서 이미지를 찾아서 대입
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// 인자로 들어온 값으로 order 세팅
void GameEngineRender::SetOrder(int _Order)
{
	Order = _Order;
	// 값을 넣어준 후에 렌더러를 소유한 오너의 Level 이 소유한 map 에 추가
	Owner->GetLevel()->PushRender(this);
}

// 프레임값 세팅
void GameEngineRender::SetFrame(int _Frame)
{
	// 이미지가 없다면
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	// Cut 이미지가 아니라면 
	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	// Index 범위를 넘어섰다면 
	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유요하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}
// 렌더링
void GameEngineRender::Render(float _DeltaTime)
{
	// 출력될 좌표는 렌더러를 소유한 액터의 위치 + 추가 포지션값
	float4 RenderPos = Owner->GetPos() + Position;

	// 커팅된 이미지라면
	if (true == Image->IsImageCutting())
	{
		// 프레임당 트랜스카피 사용
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, Scale);
	}
	// 커팅된 이미지가 아니라면
	else
	{
		// 그냥 이미지 전체를 입력된 크기로 출력한다. 
		GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, Scale, { 0, 0 }, Image->GetImageScale());
	}
}