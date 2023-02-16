#pragma once
#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCollision.h>

// 윈도우창에 보여지는 화면을 Level 또는 Sceen 이라고 한다. 
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollsion;
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;
	 
	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	// 디버그용 렌더 스위치
	static void DebugRenderSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}

	float4 GetMousePos();
	float4 GetMousePosToCamera();


	// 액터생성시 Order 타입을 인자로 받는다. 
	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

	// 레벨에서 사용할 액터 생성
	template <typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType;

		// 생성한 액터의 필요한 부분 로딩
		ActorStart(Actor , _Order);

		// 맵의 새로운 문법
		// 해당하는 키값으로, 데이터를 저장한다.
		// 데이터가 없을 경우, 그 키값으로 데이터를 저장한다.
		// 데이터가 있을 경우, 그 키값에 해당하는 데이터를 레퍼런스로 반환해준다. 
		Actors[_Order].push_back(Actor);

		// 액터를 생성하면 생성한 액터의 포인터타입으로 캐스팅하여 반환해준다. 
		return dynamic_cast<ActorType*>(Actor);
	}

	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
	}

	// 원하는 타입을 인자로 넣어주면 해당하는 타입의 배열을 반환한다. 
	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	// 레벨이 소유한 액터중 원하는 타입을 골라서 받아올 수 있음. 
	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		// 내부에서 새로운 vector 선언
		std::vector<GameEngineActor*> Result;

		// 액터리스트에 들어있는 배열 그자체를 받아온다. (레퍼런스)  
		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		
		// 새로 생성한 배열의 공간을 받아올 배열의 크기만큼 늘린다. 
		Result.reserve(Group.size());

		// 받아온 데이터를 push_back 
		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		// 데이터를 복사해준 vector 를 반환해준다. 
		return Result;
	}

	static void DebugTextPush(const std::string& _DebugText)
	{
		DebugTexts.push_back(_DebugText);
	}


protected:
	// 화면을 보여줄 때 사용할 부분들을 로드한다.
	// GameEngineDirectory 클래스를 활용하여 디렉토리를 찾고, 경로를 만든 후 그 경로에 있는 파일 로드
	// 플레이어, 몬스터, 맵 등의 이미지, 사운드 
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	
	virtual void LevelChangeEnd(GameEngineLevel * _NextLevel) = 0;
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;
	
private:
	static bool IsDebugRender;

	// 카메라 좌표
	float4 CameraPos = float4::Zero;

	static float4 TextOutStart;
	static std::vector<std::string> DebugTexts;

	// Order 값을 키값으로 하는 액터리스트를 저장한다. 
	std::map<int, std::list<GameEngineActor*>> Actors;
	
	// 업데이트와 렌더링은 기본적으로 델타타임을 받는다. 
	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);

	// 액터 생성 후 액터 로딩
	void ActorStart(GameEngineActor* _Actor, int _Order);

	// 렌더러 저장
	std::map<int, std::list<GameEngineRender*>> Renders;
	// 맵에 렌더러 추가
	void PushRender(GameEngineRender* _Render);

	// 충돌체 저장
	std::map<int, std::list<GameEngineCollision*>> Collisions;
	// 맵에 충돌체 추가  
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);

	// 엔진수준의 기능이기 때문에 private으로 둔다.
	void Release();
};