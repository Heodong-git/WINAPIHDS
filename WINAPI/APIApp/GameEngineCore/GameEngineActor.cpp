#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineLevel.h"
#include "GameEngineCollision.h"

GameEngineActor::GameEngineActor()
{
}

// 자신이 동적할당한 메모리들을 자신의 소멸자에서 제거한다. 
GameEngineActor::~GameEngineActor()
{
	// ranged for 문법사용
	// 렌더러리스트를 순회하며 동적할당된 메모리를 해제
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}

	// 충돌체리스트를 순회하며 동적할당된 메모리 해제
	for (GameEngineCollision* _Collision : CollisionList)
	{
		if (nullptr == _Collision)
		{
			continue;
		}

		delete _Collision;
		_Collision = nullptr;
	}
}

// 나 자신을 소유한 레벨을 반환
GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

// 렌더생성
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order /*= 0*/)
{
	// 오버로딩된 함수를 호출
	GameEngineRender* Render = CreateRender(_Order);
	// 렌더러가 출력할 이미지 세팅
	Render->SetImage(_Image);

	// 생성된 렌더 객체의 주소값 반환
	return Render;
}

// 렌더생성
GameEngineRender* GameEngineActor::CreateRender(int _Order /*= 0*/)
{	
	// 렌더러 동적할당
	GameEngineRender* Render = new GameEngineRender();

	// 렌더의 부모, 렌더링오더 세팅
	// 액터가 소유한 렌더러 리스트에 추가
	Render->SetOwner(this);
	Render->SetOrder(_Order);
	RenderList.push_back(Render);

	// 생성된 렌더러 객체의 주소값 반환
	return Render;
}

// 충돌체 생성함수
GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	// 충돌체 클래스 동적할당
	GameEngineCollision* Collision = new GameEngineCollision();

	// 오너 세팅 , Collision 그룹값 세팅 , 리스트에 추가
	Collision->SetOwner(this);
	// 인자로 들어온 그룹 값을 넣어준다.
	Collision->SetOrder(_GroupIndex);
	CollisionList.push_back(Collision);
	
	// 생성한 충돌체 반환 
	return Collision;
}

void GameEngineActor::Release()
{
	{
		std::list<GameEngineRender*>::iterator StartIter = RenderList.begin();
		std::list<GameEngineRender*>::iterator EndIter = RenderList.end();

		// 렌더리스트 순회
		for (; StartIter != EndIter; )
		{
			GameEngineRender* ReleaseRender = *StartIter;

			if (nullptr == ReleaseRender)
			{
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
			}

			// 렌더가 데스상태가 아니라면 지우지 않고 다음 노드로 이동 후 조건문으로. 
			if (false == ReleaseRender->IsDeath())
			{
				++StartIter;
				continue;
			}

			// 코드가 내려왔다면 데스상태이기 때문에 리스트에서 지워준다. 
			StartIter = RenderList.erase(StartIter);

			// 지워진 녀석의 주소값을 알고 있기 때문에 메모리에서 제거 후 nullptr 초기화
			delete ReleaseRender;
			ReleaseRender = nullptr;
		}
	}
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineCollision* ReleaseCollision = *StartIter;

			if (nullptr == ReleaseCollision)
			{
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
			}

			if (false == ReleaseCollision->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = CollisionList.erase(StartIter);

			delete ReleaseCollision;
			ReleaseCollision = nullptr;
		}
	}
}