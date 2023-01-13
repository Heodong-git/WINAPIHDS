#include "GameEngineActor.h"
#include "GameEngineRender.h"

GameEngineActor::GameEngineActor()
{
}

GameEngineActor::~GameEngineActor()
{
	// 렌더리스트를 순회하여 저장되어있는 동적할당된 메모리를 모두 해제
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}
}

// 인자로 넣어준 이미지, Order 값으로 렌더클래스생성
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	// 오버로딩된 함수를 호출
	GameEngineRender* Render = CreateRender(_Order);
	// 렌더러가 출력할 이미지 세팅
	Render->SetImage(_Image);

	// 작업 완료된 객체 반환
	return Render;
}


GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{	
	// 렌더러 동적할당
	GameEngineRender* Render = new GameEngineRender();

	// 같은행동이지만 임시로 일단 둘다 냅둠 
	Render->SetParent(this);
	// Renderer 오너 = this ( 이함수를 호출한 객체의 주소 ) 
	Render->Owner = this;
	// Zorder 값 세팅
	Render->SetOrder(_Order);
	// 액터가 소유한 리스트에 넣어준다. 
	RenderList.push_back(Render);

	// 작업완료된 렌더러 반환
	return Render;
}