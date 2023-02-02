#pragma once
#include <vector>
#include "GameEngineComponent.h"

// 가독성을 위해 enum class가 아닌 enum 사용
// 기본적으로는 enum class 의 가독성이 뛰어나지만
// 함수의 인자로 새로운 문법을 사용하려고 할 때 코드가 너무 길어져서 enum 을 사용하여 가독성을 높이는 용도
// 단점을 보완하기 위해 값의 이름 앞에 CT_ 를 붙여준다. 
enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

// 충돌체크 정보를 저장하기 위한 변수
class CollisionCheckParameter
{
public:
	// 여러분들이 제대로 어떤 그룹과 충돌할지 안해주면
	int TargetGroup = -342367842;
	CollisionType TargetColType = CollisionType::CT_CirCle;
	CollisionType ThisColType = CollisionType::CT_CirCle;
};

// 충돌체를 사용하지 않고 그냥 원대원으로 충돌시키려고 할 때 사용하려고 만듦. 
class CollisionData
{
public:
	float4 Position;
	// X값만 원의 반지름으로. 
	float4 Scale; 

	float Left() const
	{
		return Position.x - Scale.hx();
	}
	float Right() const
	{
		return Position.x + Scale.hx();
	}
	float Top() const
	{
		return Position.y - Scale.hy();
	}
	float Bot() const
	{
		return Position.y + Scale.hy();
	}
};

class CollisionFunctionInit;
class GameEngineCollision : public GameEngineComponent
{
	friend CollisionFunctionInit;

private:

public:
	// 현재로써는 원대원충돌만 구현 
	static bool CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right);

	static bool CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right);


	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	void SetOrder(int _Order) override;

	CollisionData GetCollisionData();

	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

	void DebugRender();

protected:

private:
	// 충돌체 자신이 타입을 가질 수 있도록.
	CollisionType DebugRenderType = CollisionType::CT_CirCle;
};

