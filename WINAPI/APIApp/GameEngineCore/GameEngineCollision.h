#pragma once
#include <vector>
#include "GameEngineComponent.h"

// �������� ���� enum class�� �ƴ� enum ���
// �⺻�����δ� enum class �� �������� �پ����
// �Լ��� ���ڷ� ���ο� ������ ����Ϸ��� �� �� �ڵ尡 �ʹ� ������� enum �� ����Ͽ� �������� ���̴� �뵵
// ������ �����ϱ� ���� ���� �̸� �տ� CT_ �� �ٿ��ش�. 
enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

// �浹üũ ������ �����ϱ� ���� ����
class CollisionCheckParameter
{
public:
	int TargetGroup = -342367842;
	CollisionType TargetColType = CollisionType::CT_CirCle;
	CollisionType ThisColType = CollisionType::CT_CirCle;
};

// �浹ü�� ������� �ʰ� �׳� ��������� �浹��Ű���� �� �� ����Ϸ��� ����. 
class CollisionData
{
public:
	float4 Position;
	// X���� ���� ����������. 
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
	// �浹ü �ڽ��� Ÿ���� ���� �� �ֵ���.
	CollisionType DebugRenderType = CollisionType::CT_CirCle;
};

