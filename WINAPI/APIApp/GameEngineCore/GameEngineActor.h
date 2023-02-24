#pragma once
#include <list>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// 어떠한 Level에 속해있는 화면에 표현되는 모든것 --- Actor
class GameEngineLevel;
class GameEngineRender;
class GameEngineCollision;
class GameEngineActor : public GameEngineObject
{
	// GameEngineLevl 에서 GameEngineActor 클래스 내부에 접근 가능
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// 위치반환
	inline float4 GetPos()
	{
		return Pos;
	}

	// 위치세팅
	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// 위치이동, 기존의 자신의 좌표 + 인자로 들어온 값 
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	GameEngineLevel* GetLevel();

#pragma region CreateRenderEnumOverLoadings

	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	// 렌더러 생성, 사용할이미지, RenderOrder 값을 넣어준다. 
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

	// 충돌체생성, 충돌체그룹을 enum 값으로 지정해준다. 
	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _GroupIndex)
	{
		return CreateCollision(static_cast<int>(_GroupIndex));
	}

	GameEngineCollision* CreateCollision(int _GroupIndex = 0);


protected:
	// 클래스 생성 후 바로 해주어야할 일
	// 렌더링이 필요하다면 GameEngineRender 생성 후 사용할 이미지, Order 체크
	virtual void Start() {}

	// 키입력 + 논리적인 연산 수행
	virtual void Update(float _DeltaTime) {}

	// 최종연산수행, 사용하기 전 이걸 꼭 써야하나? 라고 생각해봐야함.
	virtual void LateUpdate(float _DeltaTime) {}

	// 연산 수행 후 화면에 출력되는 부분을 수행 
	virtual void Render(float _DeltaTime) {}

	// 현재 액터가 화면에 살아있는 시간 반환
	inline float GetLiveTime()
	{
		return LiveTime;
	}

private:

	float	LiveTime = 0.0;					 // 액터가 화면에 살아있는 시간 
	float4  Pos = { 0.0f, 0.0f };			 // 위치를 저장할 변수
	std::list<GameEngineRender*> RenderList; // 액터는 자신이 출력해야할 Render 리스트를 가진다. 
	std::list<GameEngineCollision*> CollisionList;

	void Release();
};

